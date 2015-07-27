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


#ifndef _DATATRANSLATOR_H_
#define _DATATRANSLATOR_H_

#include "Connectivity.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

class Getter
{
public:
    virtual std::vector<std::string> getPid(const int pid) = 0;
};

class CurrentGetter : public Getter
{
public:
    CurrentGetter(const std::string& dev);
    virtual std::vector<std::string> getPid(const int pid) override;

private:
    Elm327& _dev;
};

class FreezeFrameGetter : public Getter
{
public:
    FreezeFrameGetter(const std::string& dev);
    virtual std::vector<std::string> getPid(const int pid) override;

private:
    Elm327& _dev;
};


class DataTranslator
{
public:
    DataTranslator(std::shared_ptr<Getter> getter);
    std::string fuelSystemStatus();
    std::string calculatedEngineLoad();
    std::string engineCoolantTemperature();
    std::string shortTermFuelTrimBank1();
    std::string longTermFuelTrimBank1();
    std::string shortTermFuelTrimBank2();
    std::string longTermFuelTrimBank2();

private:
    std::vector<uint8_t> prepareBytes(const std::string& hexString);
    std::vector<uint8_t> prepareBytes(const std::vector<std::string>& lines);

    std::shared_ptr<Getter> _getter;
};

#endif
