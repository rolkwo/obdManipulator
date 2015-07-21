#include "DataTranslator.h"

#include "Utils.h"

#include <stdexcept>
#include <vector>

std::string DataTranslator::fuelSystemStatus(const std::string& hexString)
{
    std::vector<uint8_t> bytes = prepareBytes(hexString);

    if(bytes.size() < 1)
        throw std::runtime_error("Fuel system status should return at least one byte");

    if(bytes[0] & 1)
        return "Open loop due to insufficient engine temperature";
    else if(bytes[0] & 2)
        return "Closed loop, using oxygen sensor feedback to determine fuel mix";
    else if(bytes[0] & 4)
        return "Open loop due to engine load OR fuel cut due to deceleration";
    else if(bytes[0] & 8)
        return "Open loop due to system failure";
    else if(bytes[0] & 16)
        return "Closed loop, using at least one oxygen sensor but there is a fault in the feedback system";

    return "Invalid value";
}

std::string DataTranslator::calculatedEngineLoad(const std::string& hexString)
{
    std::vector<uint8_t> bytes = prepareBytes(hexString);

    if(bytes.size() != 1)
        throw std::runtime_error("Calculated engine load should return one byte");

    return std::to_string((bytes[0]*100)/255) + "%";
}

std::string DataTranslator::engineCoolantTemperature(const std::string& hexString)
{
    std::vector<uint8_t> bytes = prepareBytes(hexString);

    if(bytes.size() != 1)
        throw std::runtime_error("Engine coolant temperature should return one byte");

    return std::to_string(bytes[0]-40) + " Celsius degrees";
}

std::string DataTranslator::shortTermFuelTrimBank1(const std::string &hexString)
{
    auto bytes = prepareBytes(hexString);

    if(bytes.size() != 1)
        throw std::runtime_error("Short term fuel trim should return one byte");

    return std::to_string(((bytes[0] - 128) * 100) / 128) + "%";
}

std::string DataTranslator::longTermFuelTrimBank1(const std::string &hexString)
{
    auto bytes = prepareBytes(hexString);

    if(bytes.size() != 1)
        throw std::runtime_error("Long term fuel trim should return one byte");

    return std::to_string(((bytes[0] - 128) * 100) / 128) + "%";
}

std::string DataTranslator::shortTermFuelTrimBank2(const std::string &hexString)
{
    auto bytes = prepareBytes(hexString);

    if(bytes.size() != 1)
        throw std::runtime_error("Short term fuel trim should return one byte");

    return std::to_string(((bytes[0] - 128) * 100) / 128) + "%";
}

std::string DataTranslator::longTermFuelTrimBank2(const std::string &hexString)
{
    auto bytes = prepareBytes(hexString);

    if(bytes.size() != 1)
        throw std::runtime_error("Long term fuel trim should return one byte");

    return std::to_string(((bytes[0] - 128) * 100) / 128) + "%";
}

std::vector<uint8_t> DataTranslator::prepareBytes(const std::string& hexString)
{
    std::string localHex(hexString);
    Utils::removeSpaces(localHex);

    return Utils::hexStrToByteArray(localHex);
}
