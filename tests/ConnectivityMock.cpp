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


#include <Connectivity.h>

#include <iomanip>
#include <sstream>
#include <stdexcept>

#include <boost/algorithm/string.hpp>

// just for debug
#include <iostream>

std::map<std::string, Elm327*> Elm327::_devices;

Elm327& Elm327::getDevice(const std::string& device, const int baudrate)    //return fake device for tests only!!!
{
    return *(_devices[device]);
}

void Elm327::reset()
{
}

void Elm327::setProtocol(const Protocol proto)
{
}

void Elm327::disableEcho()
{
}

std::vector<std::string> Elm327::sendObd(const int mode, const int pid)
{
    if(mode == 1 && (pid == 0 || pid == 20))
        return std::vector<std::string>() = {"BE 1F B8 10"};


    return std::vector<std::string>();
}

std::vector<std::string> Elm327::sendObd(const int mode)
{
    if(mode == 3)
        return std::vector<std::string>() = {"01 33 00 00 00 00"};

    return std::vector<std::string>();
}

void Elm327::expectOk()
{
}

std::string Elm327::readLine(const char delimiter)
{
    std::string out;
    return out;
}

std::string Elm327::readTillPrompt()
{
    std::string out;
    return out;
}

void Elm327::write(const std::string& data)
{
}

void Elm327::writeLine(const std::string &data)
{
}

std::vector<std::string> Elm327::getObdLines(const int bytesToCut)
{
    return std::vector<std::string>();
}
