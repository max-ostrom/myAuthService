#include <fstream>
#include <nlohmann/json.hpp>

#include "logger.h"

#define DEFAULT_PORT 43536
#define DEFAULT_TYPE "GRPC"

struct config
{
    int port;
    std::string type;
};

config parserJson(const std::string& path);