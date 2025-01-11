#pragma once

#include "grpcauthserviceimpl.h"
#include "tokengenerator.h"
#include "shahasher.h"
#include "grpcauthservice.h"
#include "types.h"

#include <memory>

class AuthServiceFactory
{
    std::shared_ptr<grpc::ServerCredentials> setupGRPCSSLCreds()
    {
        grpc::SslServerCredentialsOptions ssl_opts;
        ssl_opts.pem_key_cert_pairs.push_back(
            grpc::SslServerCredentialsOptions::PemKeyCertPair{
                "server.key", // openssl genpkey -algorithm RSA -out server.key -aes256
                "server.crt" // openssl req -new -x509 -key server.key -out server.crt -days 3650
            });

        return grpc::SslServerCredentials(ssl_opts);
    }

    std::shared_ptr<IAuthService> BuildGRPC(const std::string& endpoint, AuthService::ProtocolEncryption encryption, std::shared_ptr<IHasher> hasher)
    {
        std::shared_ptr<ITokenGenerator> tokenGen = std::make_shared<TokenGenerator>(32);

        CachedStorage strg(tokenGen, hasher);
        GRPCAuthServiceImpl authService(strg);
        grpc::ServerBuilder builder;     

        if(encryption == AuthService::ProtocolEncryption::Insecure)
        {
            builder.AddListeningPort(endpoint, grpc::InsecureServerCredentials());
        }
        else
        {
            builder.AddListeningPort(endpoint, setupGRPCSSLCreds());
        }
        builder.RegisterService(&authService);
        std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
        
        return std::make_shared<GrpcAuthService>(std::move(server));
    }

public:
    std::shared_ptr<IAuthService> Build(size_t port,
        AuthService::ServiceProtocol protocol,
        AuthService::ProtocolEncryption encryption,
        AuthService::HashAlgorithm hasher)
    {
        std::shared_ptr<IHasher> ihasher = std::make_shared<SHAHasher>();

        std::string endpoint = "0.0.0.0:" + std::to_string(port);
        if(protocol == AuthService::ServiceProtocol::gRPC)
        {
            return BuildGRPC(endpoint, encryption, ihasher);
        }

        throw std::exception();
    }
};