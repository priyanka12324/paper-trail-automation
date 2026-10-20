#include "crypto_engine.hpp"

#include <cstdint>
#include <random>
#include <stdexcept>
#include <utility>

CryptoEngine::CryptoEngine(std::string key1, std::string key2, std::string key3)
    : k1_(std::move(key1)), k2_(std::move(key2)), k3_(std::move(key3)) {
    if (k1_.empty() || k2_.empty()) {
        throw std::invalid_argument("K1 and K2 must not be empty");
    }
}

long long CryptoEngine::generateNonce() {
    // Mirrors the supplied demo's approach. Do not treat this demo as production crypto.
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<long long> dist(100000, 999999);
    return dist(gen);
}

std::string CryptoEngine::encryptMsg(const std::string& text, long long nonce) const {
    std::string result = text;
    const std::uint8_t nonce_byte = static_cast<std::uint8_t>(nonce % 256);

    for (std::size_t i = 0; i < text.size(); ++i) {
        const std::uint8_t original = static_cast<std::uint8_t>(
            static_cast<unsigned char>(text[i]));
        const std::uint8_t k1_char = static_cast<std::uint8_t>(
            static_cast<unsigned char>(k1_[i % k1_.size()]));
        const std::uint8_t k2_char = static_cast<std::uint8_t>(
            static_cast<unsigned char>(k2_[i % k2_.size()]));
        const std::uint8_t index_byte = static_cast<std::uint8_t>(i % 256);
        const std::uint8_t mixed = original ^ k1_char ^ nonce_byte ^ index_byte;
        const std::uint8_t shift = static_cast<std::uint8_t>(
            (static_cast<unsigned int>(k2_char) +
             static_cast<unsigned int>(nonce % 256)) % 256);
        result[i] = static_cast<char>(static_cast<std::uint8_t>(mixed + shift));
    }
    return result;
}

std::string CryptoEngine::decryptMsg(const std::string& text, long long nonce) const {
    std::string result = text;
    const std::uint8_t nonce_byte = static_cast<std::uint8_t>(nonce % 256);

    for (std::size_t i = 0; i < text.size(); ++i) {
        const std::uint8_t cipher = static_cast<std::uint8_t>(
            static_cast<unsigned char>(text[i]));
        const std::uint8_t k1_char = static_cast<std::uint8_t>(
            static_cast<unsigned char>(k1_[i % k1_.size()]));
        const std::uint8_t k2_char = static_cast<std::uint8_t>(
            static_cast<unsigned char>(k2_[i % k2_.size()]));
        const std::uint8_t index_byte = static_cast<std::uint8_t>(i % 256);
        const std::uint8_t shift = static_cast<std::uint8_t>(
            (static_cast<unsigned int>(k2_char) +
             static_cast<unsigned int>(nonce % 256)) % 256);
        const std::uint8_t unshifted = static_cast<std::uint8_t>(cipher - shift);
        result[i] = static_cast<char>(unshifted ^ k1_char ^ nonce_byte ^ index_byte);
    }
    return result;
}
