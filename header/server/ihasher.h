#pragma once

#include <string>

class IHasher
{
    public:
        virtual std::string hash(const std::string& strToHash, size_t size = 32) = 0;
        virtual ~IHasher() {};
};