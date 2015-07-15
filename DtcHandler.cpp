#include "DtcHandler.h"

#include <stdexcept>

const std::map<const char, const std::string> DtcHandler::_translation = 
{ {'0', "P0"},
  {'1', "P1"}};

std::vector<DtcHandler::Dtc> DtcHandler::getCodes()
{
    std::vector<std::string> lines = _device.sendObd(3);
}

std::vector<DtcHandler::Dtc> DtcHandler::prepareCodes(const std::vector<std::string>& lines)
{
    std::vector<Dtc> ret;
    for(const auto& line : lines)
    {
        std::vector<Dtc> temp = interpretCodes(line);
        ret.insert(ret.end(), temp.begin(), temp.end());
    }

    return ret;
}

std::vector<DtcHandler::Dtc> DtcHandler::interpretCodes(const std::string& line)
{
    if(line.size() != 17)
        throw std::runtime_error("Incorrect DTC line to parse");

    std::vector<Dtc> ret;

    for(int i = 0; i < 3; ++i)
    {
        std::string code = getCode(line.substr(i * 7, 5));
        if(code.empty())
            continue;

        Dtc toAdd;
        toAdd.code = code;
        ret.push_back(toAdd);
    }

    return ret;
}

std::string DtcHandler::getCode(const std::string& twoBytes)
{
    std::string ret;

    if(twoBytes == "00 00 ")
        return ret;

    ret = _translation.at(twoBytes[0]);
    ret += twoBytes.substr(3, 2);

    return ret;
}
