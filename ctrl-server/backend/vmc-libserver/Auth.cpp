#include "Auth.h"

#include <cryptopp/cryptlib.h>
#include <cryptopp/osrng.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/base64.h>

#include "String.h"

#include <iostream>

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

// TODO: Test this performance on rpi: Get this as high as possible.
#define ITERATIONS 100000

namespace vmc
{
    namespace auth
    {
        std::string createHash(std::string const &password)
        {
            CryptoPP::AutoSeededRandomPool random;

            CryptoPP::SecByteBlock salt(CryptoPP::SHA256::DIGESTSIZE);
            random.GenerateBlock(salt, salt.size());

            CryptoPP::SecByteBlock key(CryptoPP::SHA256::DIGESTSIZE);
            CryptoPP::PKCS5_PBKDF2_HMAC<CryptoPP::SHA256> pbkdf;

            pbkdf.DeriveKey(key, key.size(), 0, (byte *) password.data(), password.size(), salt, salt.size(), ITERATIONS);

            std::string saltString;
            CryptoPP::StringSource saltSource(salt, salt.size(), true, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(saltString)));
            std::string keyString;
            CryptoPP::StringSource keySource(key, key.size(), true, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(keyString)));

            std::string hash = std::string(STR(ITERATIONS)) + ";" + saltString + ";" + keyString;
            return hash;
        }

        bool comparePassword(std::string const &hash, std::string const &password)
        {
            if (password.length() <= 0) return false;

            auto parts = string::split(hash, ";");
            int iterations = std::atoi(parts[0].c_str());
            std::string saltString = parts[1];
            std::string keyString = parts[2];

            std::string saltData;

            CryptoPP::StringSource saltSource(saltString, true, new CryptoPP::Base64Decoder(new CryptoPP::StringSink(saltData)));

            CryptoPP::SecByteBlock key(CryptoPP::SHA256::DIGESTSIZE);
            CryptoPP::PKCS5_PBKDF2_HMAC<CryptoPP::SHA256> pbkdf;

            pbkdf.DeriveKey(key, key.size(), 0, (byte *) password.data(), password.size(), (byte *) saltData.data(), saltData.size(), iterations);

            std::string keyString2;
            CryptoPP::StringSource keySource(key, key.size(), true, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(keyString2)));

            return keyString == keyString2;
        }
    }
}
