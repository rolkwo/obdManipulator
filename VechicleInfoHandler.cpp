#include "Utils.h"
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

    Utils::removeSpaces(oneLine);

    std::string vin = Utils::hexStrToStr(oneLine);

    return vin;
}
