#ifndef AUTOMATHAUS_CRYPTO_H
#define AUTOMATHAUS_CRYPTO_H

class AutomathausCrypto {
   public:
    AutomathausCrypto(){};
    virtual ~AutomathausCrypto(){};

    virtual int encrypt(const char *input, size_t input_len,
                        unsigned char *output, size_t *output_len, const char *key) = 0;
    virtual int decrypt(const unsigned char *input, size_t input_len,
                        unsigned char *output, size_t *output_len, const char *key) = 0;
};

#endif