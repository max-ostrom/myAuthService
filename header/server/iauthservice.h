#pragma once

class IAuthService
{
public: 
    virtual void run() = 0; 
    virtual ~IAuthService(){}
};
