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


#include "DtcHandler.h"

#include "Utils.h"

#include <ostream>
#include <stdexcept>

const std::map<const char, const std::string> DtcHandler::_translation = 
{ {'0', "P0"},
  {'1', "P1"},
  {'2', "P2"},
  {'3', "P3"},

  {'4', "C0"},
  {'5', "C1"},
  {'6', "C2"},
  {'7', "C3"},

  {'8', "B0"},
  {'9', "B1"},
  {'A', "B2"},
  {'B', "B3"},

  {'C', "U0"},
  {'D', "U1"},
  {'E', "U2"},
  {'F', "U3"} };

std::vector<DtcHandler::Dtc> DtcHandler::getCodes()
{
    std::vector<std::string> lines = _device.sendObd(3);

    std::vector<Dtc> ret;

    ret = prepareCodes(lines);

    return ret;
}

void DtcHandler::resetCodes()
{
    _device.sendObd(4);
}

std::vector<DtcHandler::Dtc> DtcHandler::prepareCodes(const std::vector<std::string>& lines)
{
    std::vector<Dtc> ret;
    for(const auto& line : lines)
    {
        std::vector<Dtc> temp = interpretCodes(line);
        ret.insert(ret.end(), temp.begin(), temp.end());
    }

    return ret;
}

std::vector<DtcHandler::Dtc> DtcHandler::interpretCodes(const std::string& line)
{
    if(line.size() != 17)
        throw std::runtime_error("Incorrect DTC line to parse");

    std::string lineNoSpaces = line;
    Utils::removeSpaces(lineNoSpaces);

    std::vector<Dtc> ret;

    for(int i = 0; i < 3; ++i)
    {
        std::string code = getCode(lineNoSpaces.substr(i * 4, 4));
        if(code.empty())
            continue;

        Dtc toAdd;
        toAdd.code = code;
        ret.push_back(toAdd);
    }

    return ret;
}

std::string DtcHandler::getCode(const std::string& twoBytes)
{
    std::string ret;

    if(twoBytes == "0000")
        return ret;

    ret = _translation.at(twoBytes[0]);
    ret += twoBytes.substr(1, 3);

    return ret;
}

std::ostream& operator<<(std::ostream& out, const DtcHandler::Dtc& dtc)
{
    out << dtc.code;

    if(!dtc.verbouse.empty())
    {
        out << "\n" << dtc.verbouse;
    }

    if(!dtc.resolution.empty())
    {
        out << "\n" << dtc.resolution;
    }

    return out;
}
