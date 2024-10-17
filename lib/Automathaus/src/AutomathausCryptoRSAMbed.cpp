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


AutomathausCryptoRSAMbed::~AutomathausCryptoRSAMbed() {
    mbedtls_pk_free(&_pk);
    mbedtls_entropy_free(&_entropy);
    mbedtls_ctr_drbg_free(&_ctr_drbg);
}