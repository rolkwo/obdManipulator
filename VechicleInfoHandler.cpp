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


#include "Utils.h"
#include "VechicleInfoHandler.h"

#include <sstream>
#include <vector>

std::string VechicleInfoHandler::getVin()
{
    std::vector<std::string> lines = _device.sendObd(9, 2);

    return processLines(lines);
}

std::string VechicleInfoHandler::processLines(const std::vector<std::string>& lines)
{
    std::string oneLine;

    for(const auto& line : lines)
        oneLine += line;

    Utils::removeSpaces(oneLine);

    std::string vin = Utils::hexStrToStr(oneLine);

    return vin;
}
