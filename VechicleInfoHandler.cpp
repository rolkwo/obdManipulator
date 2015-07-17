#include "VechicleInfoHandler.h"

#include <algorithm>
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

    auto newEnd = std::remove(oneLine.begin(), oneLine.end(), ' ');
    oneLine.erase(newEnd, oneLine.end());

    std::string vin;
    while(!oneLine.empty())
    {
        std::string hex = oneLine.substr(0, 2);
        std::stringstream ss;

        ss << std::hex << hex;

        unsigned int c;
        ss >> c;

        oneLine.erase(0, 2);

        if(c)
            vin += c;
    }

    return vin;
}
