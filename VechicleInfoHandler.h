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
