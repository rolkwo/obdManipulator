#include "VechicleInfoHandler.h"

#include <sstream>
#include <vector>

std::string VechicleInfoHandler::getVin()
{
    std::vector<std::string> lines = _device.sendObd(9, 2);

    std::string oneLine;

    for(const auto& line : lines)
        oneLine += line;

    std::string vin;
    while(!oneLine.empty())
    {
        std::string hex = oneLine.substr(0, 2);
        std::stringstream ss(hex);

        char c;
        ss >> std::hex >> c;

        vin += c;
    }

    return vin;
}
