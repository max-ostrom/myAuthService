#include "cachedstorage.h"
#include "logger.h"

CachedStorage::CachedStorage(std::shared_ptr<ITokenGenerator> tokenGenerator, std::shared_ptr<IHasher> hasher) :m_hasher(hasher), m_tokenGenerator(tokenGenerator){}

ReturnStatus CachedStorage::verifyUser(const std::string& email, const std::string& pwd)
{
    auto iter = m_users.find(email);
    if(iter != m_users.end())
    {
        LOG << m_hasher->hash(pwd + iter->second.salt) << std::endl;
        if(m_hasher->hash(pwd + iter->second.salt) == iter->second.pwd)
        {
            return Status_OK;
        }
    }
    return Status_AuthError;
}

ReturnStatus CachedStorage::verifyToken(const std::string& email, const std::string& token)
{
    auto iter = m_tokens.find(email);
    if(iter != m_tokens.end())
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

    if(m_users.find(email) == m_users.end())
    {
        std::pair<std::string, User> newUser;
        newUser.first = email;
        User userToRegister;
        userToRegister.email = email;
        userToRegister.salt = m_tokenGenerator->generateToken();
        userToRegister.pwd = m_hasher->hash(pwd + userToRegister.salt);
        newUser.second = userToRegister;
        m_users.emplace(newUser);
        return Status_OK;
    }
    return Status_AlreadyExist;
}

ReturnStatus CachedStorage::createToken(const std::string& email, std::chrono::minutes time, std::string& outToken)
{
    auto existingTokenIter = m_tokens.find(email);
    if(existingTokenIter != m_tokens.end())
    {
        std::string newToken = m_tokenGenerator->generateToken();
        outToken = newToken;
        existingTokenIter->second = outToken;
    }
    else
    {
        std::string newToken = m_tokenGenerator->generateToken();
        outToken = newToken;
        m_tokens[email] = newToken;
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