#ifndef _DTCREADER_H_
#define _DTCRAEDER_H_

#include "Connectivity.h"

#include <map>
#include <string>
#include <vector>

class DtcHandler
{
public:
    struct Dtc
    {
        std::string code;
        std::string verbouse;
        std::string resolution;
    };

    DtcHandler(const std::string& dev)
    : _device(Elm327::getDevice(dev))
    {
    }

    std::vector<Dtc> getCodes();

private:
    std::vector<Dtc> prepareCodes(const std::vector<std::string>& lines);
    std::vector<Dtc> interpretCodes(const std::string& line);
    std::string getCode(const std::string& twoBytes);

    Elm327& _device;

    static const std::map<const char, const std::string> _translation;
};

#endif
