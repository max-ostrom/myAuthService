#pragma once

#include "ihasher.h"

#include <sstream>
#include <iomanip>

#include <openssl/evp.h>

class SHAHasher : public IHasher    
{
public:
    virtual std::string hash(const std::string& strToHash, size_t size = EVP_MAX_MD_SIZE) override
    {
        EVP_MD_CTX* mdctx = EVP_MD_CTX_new(); // Create a new context for the hash operation
        const EVP_MD* md = EVP_sha256(); // Use SHA-256 algorithm

        // Initialize the context with SHA-256
        EVP_DigestInit_ex(mdctx, md, NULL);

        // Update the hash with the input data
        EVP_DigestUpdate(mdctx, strToHash.c_str(), strToHash.length());

        // Finalize the hash and get the result
        unsigned char hash[EVP_MAX_MD_SIZE];  // Output buffer for the hash
        unsigned int length = 0;
        EVP_DigestFinal_ex(mdctx, hash, &length);

        // Clean up the context
        EVP_MD_CTX_free(mdctx);

            // clarify does unsigned char & char same or not...
            // Convert the hash to a hexadecimal string
        std::stringstream ss;
        for (unsigned int i = 0; i < length; ++i) 
        {
            ss << std::setw(2) << std::setfill('0') << std::hex << (int)hash[i];
        }
        return ss.str();
    }
};
