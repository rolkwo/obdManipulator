#include "DataTranslator.h"

#include "Utils.h"

#include <stdexcept>
#include <vector>

DataTranslator::DataTranslator(std::shared_ptr<Getter> getter)
    : _getter(getter)
{
}

std::string DataTranslator::fuelSystemStatus()
{
    std::vector<uint8_t> bytes = prepareBytes(_getter->getPid(3));

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

std::string DataTranslator::calculatedEngineLoad()
{
    std::vector<uint8_t> bytes = prepareBytes(_getter->getPid(4));

    if(bytes.size() != 1)
        throw std::runtime_error("Calculated engine load should return one byte");

    return std::to_string((bytes[0]*100)/255) + "%";
}

std::string DataTranslator::engineCoolantTemperature()
{
    std::vector<uint8_t> bytes = prepareBytes(_getter->getPid(5));

    if(bytes.size() != 1)
        throw std::runtime_error("Engine coolant temperature should return one byte");

    return std::to_string(bytes[0]-40) + " Celsius degrees";
}

std::string DataTranslator::shortTermFuelTrimBank1()
{
    std::vector<uint8_t> bytes = prepareBytes(_getter->getPid(6));

    if(bytes.size() != 1)
        throw std::runtime_error("Short term fuel trim should return one byte");

    return std::to_string(((bytes[0] - 128) * 100) / 128) + "%";
}

std::string DataTranslator::longTermFuelTrimBank1()
{
    std::vector<uint8_t> bytes = prepareBytes(_getter->getPid(7));

    if(bytes.size() != 1)
        throw std::runtime_error("Long term fuel trim should return one byte");

    return std::to_string(((bytes[0] - 128) * 100) / 128) + "%";
}

std::string DataTranslator::shortTermFuelTrimBank2()
{
    std::vector<uint8_t> bytes = prepareBytes(_getter->getPid(8));

    if(bytes.size() != 1)
        throw std::runtime_error("Short term fuel trim should return one byte");

    return std::to_string(((bytes[0] - 128) * 100) / 128) + "%";
}

std::string DataTranslator::longTermFuelTrimBank2()
{
    std::vector<uint8_t> bytes = prepareBytes(_getter->getPid(9));

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

std::vector<uint8_t> DataTranslator::prepareBytes(const std::vector<std::string>& lines)
{
    std::string oneLine;

    for(auto& line : lines)
        oneLine += line;

    return prepareBytes(oneLine);
}

CurrentGetter::CurrentGetter(const std::string& dev)
    : _dev(Elm327::getDevice(dev))
{
}

std::vector<std::string> CurrentGetter::getPid(const int pid)
{
    return _dev.sendObd(1, pid);
}

FreezeFrameGetter::FreezeFrameGetter(const std::string& dev)
    : _dev(Elm327::getDevice(dev))
{
}

std::vector<std::string> FreezeFrameGetter::getPid(const int pid)
{
    return _dev.sendObd(1, pid);
}
