#include "requestmanager.h"

ReturnStatus GRPCRequestManager::Connect()
{
    return ReturnStatus::Status_OK;
}
ReturnStatus GRPCRequestManager::Register(const RegisterData& in, RegisterDataReply& out)
{
    auto status = m_auth->Register(&m_context, in, &out);
    if(status.ok())
    {
        return ReturnStatus::Status_OK;
    }
    return ReturnStatus::Status_Error;
}
ReturnStatus GRPCRequestManager::Login(const RegisterData& in, TokenResponse& out)
{
    auto status = m_auth->Login(&m_context, in, &out);
    if(status.ok())
    {
        return ReturnStatus::Status_OK;
    }
    return ReturnStatus::Status_Error;
} 
ReturnStatus GRPCRequestManager::RegenerateToken(const RegisterData& in, TokenResponse& out)
{
    auto status = m_auth->ExtendTokenLifetime(&m_context, in, &out);
    if(status.ok())
    {
        return ReturnStatus::Status_OK;
    }
    return ReturnStatus::Status_Error;
}