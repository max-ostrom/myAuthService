#include "cachedStorage.h"
#include "logger.h"

CachedStorage::CachedStorage(ItokenGenerator& tokenGenerator, IHasher& hasher) :m_hasher(hasher), m_tokenGenerator(tokenGenerator){}

ReturnStatus CachedStorage::verifyUser(const std::string& email, const std::string& pwd)
{
    auto iter = users.find(email);
    if(iter != users.end())
    {
        LOG << m_hasher.hash(pwd + iter->second.salt) << std::endl;
        if(m_hasher.hash(pwd + iter->second.salt) == iter->second.pwd)
        {
            return Status_OK;
        }
    }
    return Status_AuthError;
}

ReturnStatus CachedStorage::verifyToken(const std::string& email, const std::string& token)
{
    auto iter = tokens.find(email);
    if(iter != tokens.end())
    {
        if(token == iter->second)
        {
            return Status_OK;
        }
    }
    return Status_AuthError;
}

ReturnStatus CachedStorage::registerUser(const std::string& email, const std::string& pwd)
{
    if(!isEmail(email))
    {
        return Status_ValidationFailed;
    }

    if(users.find(email) == users.end())
    {
        std::pair<std::string, User> newUser;
        newUser.first = email;
        User userToRegister;
        userToRegister.email = email;
        userToRegister.salt = m_tokenGenerator.generateToken();
        userToRegister.pwd = m_hasher.hash(pwd + userToRegister.salt);
        newUser.second = userToRegister;
        users.emplace(newUser);
        return Status_OK;
    }
    return Status_AlreadyExist;
}

ReturnStatus CachedStorage::createToken(const std::string& email, std::chrono::minutes time, std::string& outToken)
{
    auto existingTokenIter = tokens.find(email);
    if(existingTokenIter != tokens.end())
    {
        std::string newToken = m_tokenGenerator.generateToken();
        outToken = newToken;
        existingTokenIter->second = outToken;
    }
    else
    {
        std::string newToken = m_tokenGenerator.generateToken();
        outToken = newToken;
        tokens[email] = newToken;
    }
    return Status_OK;
}

bool CachedStorage::isEmail(const std::string& input)
{
    size_t at = input.find('@');
    if (at == std::string::npos)
    {
        return false;
    }

    size_t dot = input.find('.', at + 1);
    if (dot == std::string::npos)
    {
        return false;
    }

    return true;
}