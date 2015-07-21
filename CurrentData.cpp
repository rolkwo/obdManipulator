#include "CurrentData.h"

#include <vector>

std::string CurrentData::fuelSystemStatus()
{
    std::vector<std::string> lines = _dev.sendObd(1, 3);

    return DataTranslator::fuelSystemStatus(lines.front());
}

std::string CurrentData::calculatedEngineLoad()
{
    std::vector<std::string> lines = _dev.sendObd(1, 4);

    return DataTranslator::calculatedEngineLoad(lines.front());
}

std::string CurrentData::engineCoolantTemprature()
{
    std::vector<std::string> lines = _dev.sendObd(1, 5);

    return DataTranslator::engineCoolantTemperature(lines.front());
}
