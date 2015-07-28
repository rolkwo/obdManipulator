// ObdManipulator - simple tool to test your car using ELM327
// Copyright (C) 2015  Roland Kwolek
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


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

std::string DataTranslator::fuelPressure()
{
    std::vector<uint8_t> bytes = prepareBytes(_getter->getPid(0xa));

    if(bytes.size() != 1)
        throw std::runtime_error("Fuel pressure should return one byte");

    return std::to_string(bytes[0] * 3) + "kPa";
}

std::string DataTranslator::intakeManifoldAbsolutePressure()
{
    std::vector<uint8_t> bytes = prepareBytes(_getter->getPid(0xb));

    if(bytes.size() != 1)
        throw std::runtime_error("Absolute manifold pressure should return one byte");

    return std::to_string(bytes[0]) + "kPa";
}

std::string DataTranslator::engineRpm()
{
    std::vector<uint8_t> bytes = prepareBytes(_getter->getPid(0xc));

    if(bytes.size() != 2)
        throw std::runtime_error("engine RPM should return two bytes");

    return std::to_string(((bytes[0] * 256) + bytes[1]) / 4) + "RPM";
}

std::string DataTranslator::vechicleSpeed()
{
    std::vector<uint8_t> bytes = prepareBytes(_getter->getPid(0xd));

    if(bytes.size() != 1)
        throw std::runtime_error("Vechicle speed should return one byte");

    return std::to_string(bytes[0]) + "km/h";
}

std::string DataTranslator::timingAdvance()
{
    std::vector<uint8_t> bytes = prepareBytes(_getter->getPid(0xe));

    if(bytes.size() != 1)
        throw std::runtime_error("Timing advance should return one byte");

    return std::to_string((bytes[0] - 128) / 2) + "deg (relative to firs cylinder)";
}

std::string DataTranslator::intakeAirTemperature()
{
    std::vector<uint8_t> bytes = prepareBytes(_getter->getPid(0xf));

    if(bytes.size() != 1)
        throw std::runtime_error("Intake air temperature should return one byte");

    return std::to_string(bytes[0]-40) + " Celsius degrees";
}

std::string DataTranslator::mafAirFlowRate()
{
    std::vector<uint8_t> bytes = prepareBytes(_getter->getPid(0x10));

    if(bytes.size() != 2)
        throw std::runtime_error("MAF air flow rate should return two bytes");

    return std::to_string(((bytes[0] * 256) + bytes[1]) / 100) + "g/s";
}

std::string DataTranslator::throttlePosition()
{
    std::vector<uint8_t> bytes = prepareBytes(_getter->getPid(0x11));

    if(bytes.size() != 1)
        throw std::runtime_error("Throttle position should return one byte");

    return std::to_string((bytes[0] * 100) / 255) + "%";
}










std::string DataTranslator::timeRunWithMilOn()
{
    std::vector<uint8_t> bytes = prepareBytes(_getter->getPid(0x4d));

    if(bytes.size() != 2)
        throw std::runtime_error("Time run with MIL on should return two bytes");

    return std::to_string((bytes[0] * 256) + bytes[1]) + " minutes";
}

std::string DataTranslator::timeSinceTroubleCodesCleared()
{
    std::vector<uint8_t> bytes = prepareBytes(_getter->getPid(0x4e));

    if(bytes.size() != 2)
        throw std::runtime_error("Time since trouble codes cleared should return two bytes");

    return std::to_string((bytes[0] * 256) + bytes[1]) + " minutes";
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
