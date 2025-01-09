#include <algorithm>
#include <functional>

#include "requestManager.h"
#include "logger.h"
#include "configParser.h"
#include "SHAHasher.h"

int main() {
    std::string pwd, email, action;
    std::cin >> action;
    std::cin >> email;
    std::cin >> pwd;
    RegisterData request;
    request.set_email(email);
    request.set_pwd(pwd);

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
