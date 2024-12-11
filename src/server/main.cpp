
#include "configParser.h"
#include "grpcAuthService.h"

int main()
{
    CachedStorage strg;
    GRPCAuthService authService(strg);
    grpc::ServerBuilder builder;

    config cnfg = parserJson("config.json");
    std::string endpoint = "0.0.0.0:" + std::to_string(cnfg.port);

    builder.AddListeningPort(endpoint, grpc::InsecureServerCredentials());
    builder.RegisterService(&authService);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());


    LOG << "pre wait" << std::endl;
    server->Wait();
    LOG << "started" << std::endl;
    return 0;
}
