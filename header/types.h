#pragma once

namespace AuthService{
enum class ServiceProtocol
{
    gRPC = 0,
    RestApi,

    //... 
    Unknown,
};

enum class ProtocolEncryption
{
    Insecure = 0,
    SSL,

    //...
    Unknown
};

enum class HashAlgorithm
{
    SHA256 = 0,

    //...
    Unknown
};

ServiceProtocol convertServiceProtocol(int input)
{
    if(input == 0)
    {
        return ServiceProtocol::gRPC;
    }
    else if(input == 1)
    {
        return ServiceProtocol::RestApi;
    }
    return ServiceProtocol::Unknown;
}

HashAlgorithm convertHashAlgorithm(int input)
{
    if(input == 0)
    {
        return HashAlgorithm::SHA256;
    }
    return HashAlgorithm::Unknown;
}

ProtocolEncryption convertProtocolEncryption(int input)
{
    if(input == 0)
    {
        return ProtocolEncryption::Insecure;
    }
    else if(input == 1)
    {
        return ProtocolEncryption::SSL;
    }
    return ProtocolEncryption::Unknown;
}
}