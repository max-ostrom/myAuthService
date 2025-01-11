#include <algorithm>
#include <functional>

#include "requestmanager.h"
#include "logger.h"

int main() {
    std::string pwd, email, action;
    std::cin >> action;
    std::cin >> email;
    std::cin >> pwd;
    RegisterData request;
    request.set_email(email);
    request.set_pwd(pwd);

    RegisterDataReply response;

    std::string endpoint = "localhost:45002";
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
