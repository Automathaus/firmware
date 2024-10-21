#include "AutomathausAsyncWebServer.h"
#include "AutomathausESPWifiNetworking.h"
#include <ArduinoJson.h>
#include <mbedtls/base64.h>
AutomathausAsyncWebServer::~AutomathausAsyncWebServer() {
    // Implementazione del distruttore, se necessario
}

void AutomathausAsyncWebServer::setWebInterface(const char *webPage){
    _server.on("/", HTTP_GET, [webPage](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", webPage);
    });

    _server.on("/getRoute", HTTP_GET, [this](AsyncWebServerRequest *request){
        char route[128];

        switch (this->getMode()) {
            case WEB_SERVER_SETUP_MODE:
                snprintf(route, sizeof(route), JSON_TEMPLATE, Routes::SETUP);
                break;
            case WEB_SERVER_NORMAL_MODE:
                snprintf(route, sizeof(route), JSON_TEMPLATE, Routes::ROOT);
                break;
        }
        request->send(200, "text/json", route);
    });

    _server.on("/wifiScan", HTTP_GET, [this](AsyncWebServerRequest *request) {
        request->send(200, "application/json", this->_networking.scanWifiNetworks().c_str());
    });


    _server.on("/getPublicKey", HTTP_GET, [this](AsyncWebServerRequest *request){
        request->send_P(200, "text/plain", RSA_PUBLIC_KEY);
    });


    _server.on("/setNodeConfig", HTTP_POST, [this](AsyncWebServerRequest *request) {
        size_t decrypted_len = this->_crypto.decryptFromB64Encoded((unsigned char*)request->_tempObject, request->contentLength());
        if(decrypted_len > 0){
            Serial.println("Body decrypted");
            JsonDocument doc;

            DeserializationError error = deserializeJson(doc, request->_tempObject);
            if (error) {
                Serial.println(error.c_str());
                request->send(400, "application/json", "{\"returnValue\": \"Invalid JSON\"}");
                return;
            }

            const char* selectedNetwork;
            const char* password;
            const char* mode;
            bool configureOtherNodes;

            if (doc["selectedNetwork"].is<const char*>()) {
                selectedNetwork = doc["selectedNetwork"].as<const char*>();
            } else {
                request->send(400, "application/json", "{\"returnValue\": \"Invalid or missing 'selectedNetwork' parameter\"}");
                return;
            }

            if (doc["password"].is<const char*>()) {
                password = doc["password"].as<const char*>();
            } else {
                request->send(400, "application/json", "{\"returnValue\": \"Invalid or missing 'password' parameter\"}");
                return;
            }

            if (doc["mode"].is<const char*>()) {
                mode = doc["mode"].as<const char*>();
            } else {
                request->send(400, "application/json", "{\"returnValue\": \"Invalid or missing 'mode' parameter\"}");
                return;
            }

            if (doc["configureOtherNodes"].is<bool>()) {
                configureOtherNodes = doc["configureOtherNodes"].as<bool>();
            } else {
                request->send(400, "application/json", "{\"returnValue\": \"Invalid or missing 'configureOtherNodes' parameter\"}");
                return;
            }

            //print the values
            Serial.print("Selected Network: ");
            Serial.println(selectedNetwork);
            Serial.print("Password: ");
            Serial.println(password);
            Serial.print("Mode: ");
            Serial.println(mode);
            Serial.print("Configure Other Nodes: ");
            Serial.println(configureOtherNodes);

            _kvStore->setWifiCredentials(selectedNetwork, password);
            _kvStore->setOperationalMode(mode);

            request->send(200, "application/json", "{\"returnValue\": \"Success\"}");
        }else{
            request->send(400, "application/json", "{\"returnValue\": \"Error\"}");
        }
    },
    NULL,
    handleBody).setFilter(ON_AP_FILTER);


    //test endpoint to print to serial the kvStore
    _server.on("/testKVStore", HTTP_GET, [this](AsyncWebServerRequest *request){
        Serial.println(_kvStore->getWifiSSID());
        Serial.println(_kvStore->getWifiPassword());
        Serial.println(_kvStore->getOperationalMode());
        request->send(200, "application/json", "{\"returnValue\": \"Success\"}");
    });


    _server.onNotFound([](AsyncWebServerRequest *request){
        request->redirect("/");
    });

    // DefaultHeaders::Instance().addHeader("Automathaus-Node-ID", "1");
}



void AutomathausAsyncWebServer::handleBody(AsyncWebServerRequest *request, uint8_t *data,size_t len, size_t index, size_t total) {
    if (total > 0 && request->_tempObject == NULL &&
        total < _maxContentLength) {
        request->_tempObject = malloc(total);
    }
    if (request->_tempObject != NULL) {
        memcpy((uint8_t *)(request->_tempObject) + index, data, len);
    }
}



size_t AutomathausAsyncWebServer::decryptEncryptedBody(AsyncWebServerRequest *request) {
    if(request->contentLength() > MBEDTLS_MPI_MAX_SIZE){
        request->send(400, "application/json", "{\"returnValue\": \"Too long for encryption\"}");
        return -1;
    }

    //Base64 decode the encrypted data
    unsigned char decoded[MBEDTLS_MPI_MAX_SIZE];
    size_t decoded_len = 0;
    mbedtls_base64_decode(decoded, MBEDTLS_MPI_MAX_SIZE, &decoded_len, (unsigned char*)request->_tempObject, request->contentLength());

    Serial.print("Decoded message 64: ");
    Serial.write(decoded, decoded_len);
    Serial.println();

    if(decoded_len > 256){
        request->send(400, "application/json", "{\"returnValue\": \"Too long for encryption\"}");
        return -1;
    }

    // Buffer to hold the decrypted data
    unsigned char decrypted[MBEDTLS_MPI_MAX_SIZE];
    size_t decrypted_len = 0;

    if(_crypto.decrypt(decoded, decoded_len, decrypted, &decrypted_len, RSA_PRIVATE_KEY) == 0){
        Serial.print("Decrypted message: ");
        Serial.write(decrypted, decrypted_len);
        Serial.println("Length: ");
        Serial.print(decrypted_len);
        Serial.println();
    }else{
        request->send(400, "application/json", "{\"returnValue\": \"Decryption failed\"}");
        return -1;
    }

    //erase temp object with memset
    memset(request->_tempObject, 0, request->contentLength());
    //write the decrypted data to the temp object
    memcpy(request->_tempObject, decrypted, decrypted_len);
    return decrypted_len + 1;
}


void AutomathausAsyncWebServer::begin(AutomathausKeyValueStore &kvStore){
    (void)_networking.scanWifiNetworks();
    _kvStore = &kvStore;
    setGeneratedBindings();
    _server.begin();
}









//Used for testing
// _server.on("/sendEncryptedDataInJSON", HTTP_POST, [this](AsyncWebServerRequest *request) {
//     JsonDocument doc;

//     DeserializationError error = deserializeJson(doc, request->_tempObject);
//     if (error) {
//         Serial.println(error.c_str());
//         request->send(400, "application/json", "{\"returnValue\": \"Invalid JSON\"}");
//         return;
//     }

//     const char* encryptedData = doc["data"];
//     char decryptedData[strlen(encryptedData) + 1];
//     strncpy(decryptedData, encryptedData, strlen(encryptedData) + 1);
//     size_t decrypted_len = this->_crypto.decryptFromB64Encoded((unsigned char*)decryptedData, strlen(decryptedData));

//     request->send(200, "application/json", decryptedData);
// },
// NULL,
// handleBody);

// _server.on("/sendEncryptedBody", HTTP_POST, [this](AsyncWebServerRequest *request) {
//     // (void)decryptEncryptedBody(request);
//     (void)this->_crypto.decryptFromB64Encoded((unsigned char*)request->_tempObject, request->contentLength());
//     request->send(200, "application/json", (char*)request->_tempObject);
// },
// NULL,
// handleBody);