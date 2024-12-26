#pragma once

#include <grpcpp/grpcpp.h>
#include <grpcpp/server_builder.h>

#include <proto/service.pb.h>
#include <proto/service.grpc.pb.h>

#include "cachedStorage.h"
#include "logger.h"

class GRPCAuthService : public Auth::Service
{
    public:
        GRPCAuthService(CachedStorage& strg);
        ::grpc::Status Register(::grpc::ServerContext* context, const ::RegisterData* request, ::RegisterDataReply* response);
        ::grpc::Status Login(::grpc::ServerContext* context, const ::RegisterData* request, ::TokenResponse* response);
        ::grpc::Status ExtendTokenLifetime(::grpc::ServerContext* context, const ::RegisterData* request, ::TokenResponse* response);
        ::grpc::Status SendMsg(::grpc::ServerContext* context, const ::Message* request, ::ResponseData* response);
    private:
        CachedStorage& m_strg;
};