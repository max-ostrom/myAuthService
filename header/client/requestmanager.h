#include "irequestmanager.h"

#include <memory>
#include <string>
#include "grpcpp/grpcpp.h"

class GRPCRequestManager : public IRequestManager
{
private:

    std::string m_serverAddress;
    std::shared_ptr<grpc::Channel> m_channel;
    std::unique_ptr<Auth::Stub> m_auth;
    grpc::ClientContext m_context;
public:
    GRPCRequestManager(const std::string& endpoint) 
    {
        m_serverAddress = endpoint;
        m_channel = grpc::CreateChannel(m_serverAddress, grpc::InsecureChannelCredentials());
        m_auth = Auth::NewStub(m_channel);
    }

    virtual ReturnStatus Connect() override;
    virtual ReturnStatus Register(const RegisterData& in, RegisterDataReply& out) override;
    virtual ReturnStatus Login(const RegisterData& in, TokenResponse& out) override;    
    virtual ReturnStatus RegenerateToken(const RegisterData& in, TokenResponse& out) override;
};

