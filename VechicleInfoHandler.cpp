#include "VechicleInfoHandler.h"

#include <sstream>
#include <vector>

std::string VechicleInfoHandler::getVin()
{
    std::vector<std::string> lines = _device.sendObd(9, 2);

    return processLines(lines);
}

std::string VechicleInfoHandler::processLines(const std::vector<std::string>& lines)
{
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
        oneLine.erase(0, 3);
    }

    return vin;
}
