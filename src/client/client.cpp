#include <algorithm>
#include <functional>

#include "requestManager.h"
#include "logger.h"
#include "configParser.h"

int main() {
    std::string pwd, email, action;
    std::cin >> action;
    std::cin >> email;
    std::cin >> pwd;
    std::hash<std::string> hasher;
    size_t pwdhash = hasher(pwd);

    RegisterData request;
    request.set_email(email);
    request.set_pwd(pwdhash);
    LOG << pwdhash << std::endl;
    RegisterDataReply response;

    config cnfg = parserJson("config.json");
    std::string endpoint = "localhost:" + std::to_string(cnfg.port);
    GRPCRequestManager manager(endpoint);
    if(action == "r")
    {  
        LOG << manager.Register(request,response) << std::endl;
    }
    else
    {
        TokenResponse token;
        LOG << manager.Login(request,token) << std::endl;
    }
    LOG << "Done" << std::endl;
    return 0;
}
