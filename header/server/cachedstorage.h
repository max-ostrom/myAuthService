#pragma once

#include <string>
#include <map>
#include <chrono>
#include <memory>

#include "status.h"

#include "itokengenerator.h"
#include "ihasher.h"

#define emailString std::string

struct User
{
    emailString email;
    std::string pwd;
    std::string salt;
};

class CachedStorage
{
    public:
        CachedStorage(std::shared_ptr<ITokenGenerator> tokenGenerator, std::shared_ptr<IHasher> hasher);
        ReturnStatus verifyUser(const emailString& email, const std::string& pwd);
        ReturnStatus verifyToken(const emailString& email, const std::string& token);
        ReturnStatus registerUser(const emailString& email, const std::string& pwd);
        ReturnStatus createToken(const emailString& email, std::chrono::minutes time, std::string& outToken);
    private:

        bool isEmail(const std::string& input);

        // use emailString to not smashed with other strings
        std::map<emailString, User> m_users;
        std::map<emailString, std::string> m_tokens;

        // replace with SHA256 + salt
        std::shared_ptr<IHasher> m_hasher;

        std::shared_ptr<ITokenGenerator> m_tokenGenerator;
};