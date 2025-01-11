
#include "grpcservicefactory.h"

#include <memory>

#include <boost/program_options.hpp>

void buildAndRun(size_t port,
    AuthService::ServiceProtocol protocol,
    AuthService::ProtocolEncryption encryption,
    AuthService::HashAlgorithm hasher)
{
    AuthServiceFactory factory;
    auto service = factory.Build(port, protocol, encryption, hasher);
    service->run();
    LOG << "started" << std::endl;
}

int main(int argc, char* argv[]) {
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help", "Produce help message")
        ("verbose,v", "Enable verbose output")
        ("type,t", boost::program_options::value<int>()->default_value(0), "Service protocol type: 0)gRPC(default) or 1)RESTAPI")
        ("port,p", boost::program_options::value<size_t>()->default_value(45554), "Service port")
        ("security,s", boost::program_options::value<int>()->default_value(0), "Service encryption data: 0)Insecure(default)")
        ("hash,hs", boost::program_options::value<int>()->default_value(0),"Hashing algorithm for passwords: 0)SHA256")
        ("roles,r", "Enables roles for users");

    boost::program_options::variables_map vm;
    try {
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
        boost::program_options::notify(vm);
    } catch (const boost::program_options::error& e) {
        LOG << "Error parsing arguments: " << e.what() << std::endl;
        return 1;
    }


//getting args
    if (vm.count("help")) {
        LOG << desc << std::endl;
        return 0;
    }
    size_t port = 0;
    AuthService::ServiceProtocol protocol = AuthService::ServiceProtocol::gRPC;
    AuthService::ProtocolEncryption encryption = AuthService::ProtocolEncryption::Insecure;
    AuthService::HashAlgorithm hasher = AuthService::HashAlgorithm::SHA256;
    if(vm.count("type"))
    {
        protocol = AuthService::convertServiceProtocol(vm["type"].as<int>());
    }
    if(vm.count("port"))
    {
        port = vm["port"].as<size_t>();
    }
    if(vm.count("security"))
    {
        encryption = AuthService::convertProtocolEncryption(vm["security"].as<int>());
    }
    if(vm.count("hash"))
    {
        hasher = AuthService::convertHashAlgorithm(vm["hash"].as<int>());
    }

//build and run service
    buildAndRun(port, protocol, encryption, hasher);


    return 0;
}
