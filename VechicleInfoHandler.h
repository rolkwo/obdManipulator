#ifndef _VECHICLEINFOHANDLER_H_
#define _VECHICLEINFOHANDLER_H_

#include "Connectivity.h"

#include <string>

class VechicleInfoHandler
{
public:
    VechicleInfoHandler(const std::string& dev)
    : _device(Elm327::getDevice(dev))
    {
    }

    std::string getVin();

protected:
    std::string processLines(const std::vector<std::string>& lines);

    Elm327& _device;
};

#endif
