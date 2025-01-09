#include "grpcAuthService.h"

GRPCAuthService::GRPCAuthService(CachedStorage& strg) : m_strg(strg){}

::grpc::Status GRPCAuthService::Register(::grpc::ServerContext* context, const ::RegisterData* request, ::RegisterDataReply* response) 
{
    LOG << request->email() << " " << request->pwd() << std::endl;
    auto status = m_strg.registerUser(request->email(),request->pwd());
    if(status == Status_AlreadyExist)
    {
        return grpc::Status(grpc::StatusCode::ALREADY_EXISTS, "exist");
    }
    else if(status == Status_ValidationFailed)
    {
        return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "no valid email");
    }
    return grpc::Status::OK;
}

::grpc::Status GRPCAuthService::Login(::grpc::ServerContext* context, const ::RegisterData* request, ::TokenResponse* response)
{
    LOG << std::endl;
    if(m_strg.verifyUser(request->email(),request->pwd()) == Status_OK)
    {
        std::string responseToken;
        if(m_strg.createToken(request->email(), std::chrono::minutes(30) ,responseToken) == Status_OK)
        {
            response->set_token(responseToken);
            return grpc::Status::OK;
        }
    }
    return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "failed");
}

::grpc::Status GRPCAuthService::ExtendTokenLifetime(::grpc::ServerContext* context, const ::RegisterData* request, ::TokenResponse* response)
{
    LOG << std::endl;
    return grpc::Status::OK;
}

::grpc::Status GRPCAuthService::SendMsg(::grpc::ServerContext* context, const ::Message* request, ::ResponseData* response)
{
    LOG << std::endl;
    return grpc::Status::OK;
}
  