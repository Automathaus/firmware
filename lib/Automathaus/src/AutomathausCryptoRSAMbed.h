#ifndef AUTOMATHAUS_CRYPTO_RSA_MBED_H
#define AUTOMATHAUS_CRYPTO_RSA_MBED_H

#include <Arduino.h>
#include "mbedtls/rsa.h"
#include "mbedtls/pk.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/sha256.h"
#include "mbedtls/error.h"
#include "mbedtls/base64.h"
#include "AutomathausCrypto.h"

#include "generated/RSAkeys.h"

class AutomathausCryptoRSAMbed : public AutomathausCrypto {
    private:
        // MbedTLS contexts and initialization structures
        mbedtls_pk_context _pk;
        mbedtls_ctr_drbg_context _ctr_drbg;
        mbedtls_entropy_context _entropy;
        int _loadKey(const char *key);

    public:
        AutomathausCryptoRSAMbed();
        ~AutomathausCryptoRSAMbed();

        int encrypt(const char *input, size_t input_len, unsigned char *output, size_t *output_len, const char *key) override final;
        int decrypt(const unsigned char *input, size_t input_len, unsigned char *output, size_t *output_len, const char *key) override final;

        size_t decryptFromB64Encoded(unsigned char *buffer, size_t buffer_len) override final;
};
#endif