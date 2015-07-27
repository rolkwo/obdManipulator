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


#ifndef _DTCREADER_H_
#define _DTCREADER_H_

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
    void resetCodes();

private:
    std::vector<Dtc> prepareCodes(const std::vector<std::string>& lines);
    std::vector<Dtc> interpretCodes(const std::string& line);
    std::string getCode(const std::string& twoBytes);

    Elm327& _device;

    static const std::map<const char, const std::string> _translation;
};

std::ostream& operator<<(std::ostream& out, const DtcHandler::Dtc& dtc);

#endif
