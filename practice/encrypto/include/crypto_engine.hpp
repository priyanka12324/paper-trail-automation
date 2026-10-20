#ifndef CRYPTO_ENGINE_HPP
#define CRYPTO_ENGINE_HPP

#include <string>

class CryptoEngine {
public:
    CryptoEngine(std::string key1, std::string key2, std::string key3);

    long long generateNonce();
    std::string encryptMsg(const std::string& text, long long nonce) const;
    std::string decryptMsg(const std::string& text, long long nonce) const;

private:
    std::string k1_;
    std::string k2_;
    std::string k3_;
};

#endif
