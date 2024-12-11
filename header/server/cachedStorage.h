#include <string>
#include <map>
#include <chrono>

#include "status.h"

struct User
{
    std::string email;
    size_t pwd;
};

class CachedStorage
{
    public:
        ReturnStatus verifyUser(const std::string& email, size_t pwd)
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
        ReturnStatus registerUser(const User& usr) 
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
        ReturnStatus createToken(const User& usr, std::chrono::minutes time, std::string& outToken)
        {
            return Status_OK;
        }
    private:

        bool isEmail(const std::string& input)
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
        ReturnStatus createNewToken(const User& usr, std::chrono::minutes time, std::string& outToken)
        {
            return Status_OK;
        }
        // first hash of email + hash of pwd -> second alive token
        std::map<std::string, std::string> cacheTokens;
        std::map<size_t, size_t> users;
        std::hash<std::string> hasher;
};