#include "status.h"

#include "proto/service.grpc.pb.h"

class IRequestManager
{
public:
    virtual ~IRequestManager() {}

    virtual ReturnStatus Connect() = 0;
    virtual ReturnStatus Register(const RegisterData& in, RegisterDataReply& out) = 0;
    virtual ReturnStatus Login(const RegisterData& in, TokenResponse& out) = 0;    
    virtual ReturnStatus RegenerateToken(const RegisterData& in, TokenResponse& out) = 0;
};