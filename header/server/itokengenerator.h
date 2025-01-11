#pragma once

#include <string>

class ITokenGenerator
{
public:
    virtual std::string generateToken() = 0;
    virtual ~ITokenGenerator(){}
};