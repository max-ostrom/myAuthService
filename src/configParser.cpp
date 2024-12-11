#include "configParser.h"

config parserJson(const std::string& path)
{
    std::ifstream f(path);
    config result;
    try
    {
        nlohmann::json data = nlohmann::json::parse(f);
        
        result.port = data["port"];
        result.type = data["type"];

        LOG << "Using " << result.port << " type: " <<  result.type << std::endl;
    }
    catch(...)
    {
        LOG << "Unable to parse config using default config..." << std::endl;
        result.port = DEFAULT_PORT;
        result.type = DEFAULT_TYPE;
    }
    return result;
}