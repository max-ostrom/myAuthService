#pragma once

#include <string>

class ItokenGenerator
{
public:
    virtual std::string generateToken() = 0;
    virtual ~ItokenGenerator(){}
};