#pragma once

#include "iauthservice.h"

#include "grpcauthserviceimpl.h"

class GrpcAuthService : public IAuthService
{
private:
    std::unique_ptr<grpc::Server> m_service;
public:
    GrpcAuthService(std::unique_ptr<grpc::Server>&& service): m_service(std::move(service)) {}
    virtual void run() override 
    {
        m_service->Wait();
    }
};