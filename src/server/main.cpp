
#include "configParser.h"
#include "grpcAuthService.h"
#include "tokenGenerator.h"
#include "SHAHasher.h"

#include <memory>

#include <boost/program_options.hpp>

void run(const std::string& cnfgPath)
{
    TokenGenerator tokenGen(32);
    SHAHasher hasher;
    CachedStorage strg(tokenGen, hasher);
    GRPCAuthService authService(strg);
    grpc::ServerBuilder builder;

    config cnfg = parserJson(cnfgPath);
    std::string endpoint = "0.0.0.0:" + std::to_string(cnfg.port);

    builder.AddListeningPort(endpoint, grpc::InsecureServerCredentials());
    builder.RegisterService(&authService);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());


    LOG << "setup done" << std::endl;
    server->Wait();
    LOG << "started" << std::endl;
}

int main(int argc, char* argv[]) {
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help", "Produce help message")
        ("verbose,v", "Enable verbose output")
        ("cnfgfile,f", boost::program_options::value<std::string>()->default_value("config.json"), "Config file path");

    boost::program_options::variables_map vm;
    try {
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
        boost::program_options::notify(vm);
    } catch (const boost::program_options::error& e) {
        LOG << "Error parsing arguments: " << e.what() << std::endl;
        return 1;
    }

    if (vm.count("help")) {
        LOG << desc << std::endl;
        return 0;
    }
    run(vm["cnfgfile"].as<std::string>());
    return 0;
}
