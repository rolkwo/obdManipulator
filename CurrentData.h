#ifndef _CURRENTDATA_H_
#define _CURRENTDATA_H_

#include "Connectivity.h"
#include "DataTranslator.h"

#include <string>

class CurrentData : public DataTranslator
{
public:
    CurrentData(const std::string& dev)
    : _dev(Elm327::getDevice(dev))
    {
    }

    std::string fuelSystemStatus();
    std::string calculatedEngineLoad();
    std::string engineCoolantTemprature();
    std::string shortTermFuelTrimBank1();
    std::string longTermFuelTrimBank1();
    std::string shortTermFuelTrimBank2();
    std::string longTermFuelTrimBank2();


private:
    Elm327& _dev;
};

#endif
