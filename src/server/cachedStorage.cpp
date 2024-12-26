#include "cachedStorage.h"

CachedStorage::CachedStorage(ItokenGenerator& tokenGenerator) : m_tokenGenerator(tokenGenerator){}

ReturnStatus CachedStorage::verifyUser(const std::string& email, size_t pwd)
{
    auto iter = users.find(hasher(email));
    if(iter != users.end())
    {
        if(pwd == iter->second)
        {
            return Status_OK;
        }
    }
    return Status_AuthError;
}

ReturnStatus CachedStorage::verifyToken(const std::string& email, const std::string& token)
{
    auto iter = tokens.find(hasher(email));
    if(iter != tokens.end())
    {
        if(token == iter->second)
        {
            return Status_OK;
        }
    }
    return Status_AuthError;
}

ReturnStatus CachedStorage::registerUser(const User& usr) 
{
    if(!isEmail(usr.email))
    {
        return Status_ValidationFailed;
    }
    size_t emailHash = hasher(usr.email);
    if(users.find(emailHash) == users.end())
    {
        std::pair<size_t, size_t> newUser;
        newUser.first = emailHash;
        newUser.second = usr.pwd;
        users.emplace(newUser);
        return Status_OK;
    }
    return Status_AlreadyExist;
}

ReturnStatus CachedStorage::createToken(const std::string& email, std::chrono::minutes time, std::string& outToken)
{
    auto emailHash = hasher(email);
    auto existingTokenIter = tokens.find(emailHash);
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
        tokens[emailHash] =newToken;
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