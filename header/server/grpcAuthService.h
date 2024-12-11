#include <grpcpp/grpcpp.h>
#include <grpcpp/server_builder.h>

#include <proto/service.pb.h>
#include <proto/service.grpc.pb.h>

#include "cachedStorage.h"
#include "logger.h"

class GRPCAuthService : public Auth::Service
{

    public:
        GRPCAuthService(CachedStorage& strg) : m_strg(strg){}
        ::grpc::Status Register(::grpc::ServerContext* context, const ::RegisterData* request, ::RegisterDataReply* response) 
        {
            LOG << "Register " << request->email() << " " << request->pwd() << std::endl;
            auto status = m_strg.registerUser({request->email(),request->pwd()});
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
        ::grpc::Status Login(::grpc::ServerContext* context, const ::RegisterData* request, ::TokenResponse* response)
        {
            LOG << "Login" << std::endl;
            if(m_strg.verifyUser(request->email(),request->pwd()) == Status_OK)
            {
                return grpc::Status::OK;
            }
            return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "failed");
        }
        ::grpc::Status ExtendTokenLifetime(::grpc::ServerContext* context, const ::RegisterData* request, ::TokenResponse* response)
        {
            LOG << "ExtendTokenLifetime" << std::endl;
            return grpc::Status::OK;
        }
        ::grpc::Status SendMsg(::grpc::ServerContext* context, const ::Message* request, ::ResponseData* response)
        {
            LOG << "SendMsg" << std::endl;
            return grpc::Status::OK;
        }
    private:
        CachedStorage& m_strg;
};