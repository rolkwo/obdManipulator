#ifndef _DATATRANSLATOR_H_
#define _DATATRANSLATOR_H_

#include <cstdint>
#include <string>
#include <vector>

class DataTranslator
{
public:
    std::string fuelSystemStatus(const std::string& hexString);
    std::string calculatedEngineLoad(const std::string& hexString);
    std::string engineCoolantTemperature(const std::string& hexString);
    std::string shortTermFuelTrimBank1(const std::string& hexString);
    std::string longTermFuelTrimBank1(const std::string& hexString);
    std::string shortTermFuelTrimBank2(const std::string& hexString);
    std::string longTermFuelTrimBank2(const std::string& hexString);

private:
    std::vector<uint8_t> prepareBytes(const std::string& hexString);
};

#endif
