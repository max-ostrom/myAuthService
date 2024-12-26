#pragma once

#include <string>
#include <map>
#include <chrono>
#include <memory>

#include "status.h"

#include "ItokenGenerator.h"

struct User
{
    std::string email;
    size_t pwd;
};

class CachedStorage
{
    public:
        CachedStorage(ItokenGenerator& tokenGenerator);
        ReturnStatus verifyUser(const std::string& email, size_t pwd);
        ReturnStatus verifyToken(const std::string& email, const std::string& token);
        ReturnStatus registerUser(const User& usr);
        ReturnStatus createToken(const std::string& email, std::chrono::minutes time, std::string& outToken);
    private:

        bool isEmail(const std::string& input);

        // first hash of email + hash of pwd -> second alive token
        std::map<std::string, std::string> cacheTokens;
        std::map<size_t, size_t> users;
        std::map<size_t, std::string> tokens;

        // replace with SHA256 + salt
        std::hash<std::string> hasher;

        ItokenGenerator& m_tokenGenerator;
};