#include "AutomathausCryptoRSAMbed.h"

AutomathausCryptoRSAMbed::AutomathausCryptoRSAMbed(){}

int AutomathausCryptoRSAMbed::_loadKey(const char *key) {
    mbedtls_pk_init(&_pk);
    mbedtls_entropy_init(&_entropy);
    mbedtls_ctr_drbg_init(&_ctr_drbg);

    const char *pers = "rsa_key";
    mbedtls_ctr_drbg_seed(&_ctr_drbg, mbedtls_entropy_func, &_entropy, (const unsigned char *)pers, strlen(pers));

    // Read the PEM-encoded key from PROGMEM
    if (mbedtls_pk_parse_key(&_pk, (const unsigned char *)key, strlen(key) + 1, NULL, 0) != 0) {
        Serial.println("Failed to load RSA key");
        return -1;
    } else {
        Serial.println("RSA key loaded successfully");
    }

    return 0;
}

int AutomathausCryptoRSAMbed::encrypt(const char *input, size_t input_len, unsigned char *output, size_t *output_len, const char *key) {
    _loadKey(key);

    // Encrypt the input data
    int ret = mbedtls_pk_encrypt(&_pk, (const unsigned char *)input, input_len, output, output_len, 2048 / 8, mbedtls_ctr_drbg_random, &_ctr_drbg);
    if (ret != 0) {
        char error_buf[100];
        mbedtls_strerror(ret, error_buf, 100);
        Serial.print("RSA encryption failed: ");
        Serial.println(error_buf);
        return -1;
    }

    Serial.println("RSA encryption successful");
    return 0;
}

int AutomathausCryptoRSAMbed::decrypt(const unsigned char *input, size_t input_len, unsigned char *output, size_t *output_len, const char *key) {
    _loadKey(key);

    // Decrypt the input data
    int ret = mbedtls_pk_decrypt(&_pk, input, input_len, output, output_len, 256, mbedtls_ctr_drbg_random, &_ctr_drbg);
    if (ret != 0) {
        char error_buf[100];
        mbedtls_strerror(ret, error_buf, 100);
        Serial.print("RSA decryption failed: ");
        Serial.println(error_buf);
        return -1;
    }

    Serial.println("RSA decryption successful");
    return 0;
}


size_t AutomathausCryptoRSAMbed::decryptFromB64Encoded(unsigned char *buffer, size_t buffer_len) {
    if(buffer_len > MBEDTLS_MPI_MAX_SIZE){
        return -1;
    }

    //Base64 decode the encrypted data
    unsigned char decoded[MBEDTLS_MPI_MAX_SIZE];
    size_t decoded_len = 0;
    mbedtls_base64_decode(decoded, MBEDTLS_MPI_MAX_SIZE, &decoded_len, (unsigned char*)buffer, buffer_len);

    Serial.print("Decoded message 64: ");
    Serial.write(decoded, decoded_len);
    Serial.println();

    if(decoded_len > 256){
        return -1;
    }

    // Buffer to hold the decrypted data
    unsigned char decrypted[MBEDTLS_MPI_MAX_SIZE];
    size_t decrypted_len = 0;

    if(decrypt(decoded, decoded_len, decrypted, &decrypted_len, RSA_PRIVATE_KEY) == 0){
        Serial.print("Decrypted message: ");
        Serial.write(decrypted, decrypted_len);
        Serial.println("Length: ");
        Serial.print(decrypted_len);
        Serial.println();
    }else{
        return -1;
    }

    //erase temp object with memset
    memset(buffer, 0, buffer_len);
    //write the decrypted data to the temp object
    memcpy(buffer, decrypted, decrypted_len);
    return decrypted_len + 1;
}



AutomathausCryptoRSAMbed::~AutomathausCryptoRSAMbed() {
    mbedtls_pk_free(&_pk);
    mbedtls_entropy_free(&_entropy);
    mbedtls_ctr_drbg_free(&_ctr_drbg);
}