#include "Utils.h"

#include "Connectivity.h"

#include <algorithm>
#include <sstream>
#include <string>

bool Utils::checkPidSupport(const std::string& dev, const int mode, const int pid)
{
    int pidToRead = (pid / 20) * 20;

    Elm327& elm = Elm327::getDevice(dev);
    std::string resp = elm.sendObd(mode, pidToRead).front();

    auto availablePids = hexStrToByteArray(resp);

    int pidInSet = pid - pidToRead;
    uint8_t bitPos = 1 << (pidInSet % 8);
    int byte = pidInSet / 8;

    return availablePids[byte] & bitPos;
}

std::string Utils::hexStrToStr(const std::string& hexStr)
{
    std::string oneLine(hexStr);
    std::string ret;

    while(!oneLine.empty())
    {
        std::string hex = oneLine.substr(0, 2);
        std::stringstream ss;

        ss << std::hex << hex;

        unsigned int c;
        ss >> c;

        oneLine.erase(0, 2);

        if(c)
            ret += c;
    }

    return ret;
}

void Utils::removeSpaces(std::string& str)
{
    auto newEnd = std::remove(str.begin(), str.end(), ' ');
    str.erase(newEnd, str.end());
}

std::vector<uint8_t> Utils::hexStrToByteArray(const std::string& hexStr)
{
    std::string str(hexStr);

    std::vector<uint8_t> ret;


    while(!str.empty())
    {
        std::string hex = str.substr(0, 2);
        std::stringstream ss;

        ss << std::hex << hex;

        uint8_t c;
        ss >> c;

        str.erase(0, 2);

        ret.push_back(c);
    }

    return ret;
}
