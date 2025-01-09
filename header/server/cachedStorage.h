#pragma once

#include <string>
#include <map>
#include <chrono>
#include <memory>

#include "status.h"

#include "ItokenGenerator.h"
#include "Ihasher.h"

struct User
{
    std::string email;
    std::string pwd;
    std::string salt;
};

class CachedStorage
{
    public:
        CachedStorage(ItokenGenerator& tokenGenerator, IHasher& hasher);
        ReturnStatus verifyUser(const std::string& email, const std::string& pwd);
        ReturnStatus verifyToken(const std::string& email, const std::string& token);
        ReturnStatus registerUser(const std::string& email, const std::string& pwd);
        ReturnStatus createToken(const std::string& email, std::chrono::minutes time, std::string& outToken);
    private:

        bool isEmail(const std::string& input);

        // first hash of email + hash of pwd -> second alive token
        std::map<std::string, std::string> cacheTokens;
        std::map<std::string, User> users;
        std::map<std::string, std::string> tokens;

        // replace with SHA256 + salt
        IHasher& m_hasher;

        ItokenGenerator& m_tokenGenerator;
};