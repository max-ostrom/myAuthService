#pragma once

#include "itokengenerator.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

class TokenGenerator : public ITokenGenerator
{
private:
    int m_tokenLenght;
public:
    TokenGenerator(int tokenLenght) : m_tokenLenght(tokenLenght)
    {}
    virtual std::string generateToken() override
    {
            boost::uuids::random_generator generator;
            boost::uuids::uuid u = generator();
            return boost::uuids::to_string(u);
    }
};
