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

Elm327& Elm327::getDevice(const std::string& device, const int baudrate)
{
    auto elm = _devices.find(device);

    if(elm != _devices.end())
        return *(elm->second);

    if(baudrate == 0)
        throw std::runtime_error("Device not found");

    _devices[device] = new Elm327(device, baudrate);

    return *(_devices[device]);
}

void Elm327::reset()
{
    writeLine("atz");
    readTillPrompt();
}

void Elm327::setProtocol(const Protocol proto)
{
    std::ostringstream oss;

    oss << "atsp" << proto;
    writeLine(oss.str());
    expectOk();
}

void Elm327::disableEcho()
{
    writeLine("ate0");

    readLine();    //to read echoed ate
    expectOk();
}

std::vector<std::string> Elm327::sendObd(const int mode, const int pid)
{
    std::ostringstream oss;

    oss << std::setfill('0') << std::setw(2) << std::setbase(16) << mode << pid;
    writeLine(oss.str());

    return getObdLines(2);
}

std::vector<std::string> Elm327::sendObd(const int mode)
{
    std::ostringstream oss;

    oss << std::setfill('0') << std::setw(2) << std::setbase(16) << mode;
    writeLine(oss.str());

    return getObdLines(1);
}

void Elm327::expectOk()
{
    std::string line = readLine();

    if(line != "OK")
        throw std::runtime_error("Expected OK while response is " + line);

    readTillPrompt();
}

std::string Elm327::readLine(const char delimiter)
{
    std::string out;

    char c;
    while(_serial.read_some(boost::asio::buffer(&c, 1)))
    {
        if(c == delimiter)
            break;

        out += c;
    }

    return out;
}

std::string Elm327::readTillPrompt()
{
    std::string out;

    char c;

    while(_serial.read_some(boost::asio::buffer(&c, 1)))
    {
        if(c == '>')
            break;

        out += c;
    }

    return out;
}

void Elm327::write(const std::string& data)
{
    _serial.write_some(boost::asio::buffer(data));
}

void Elm327::writeLine(const std::string &data)
{
    write(data);
    write("\r");
}

std::vector<std::string> Elm327::getObdLines(const int bytesToCut)
{
    std::string resp = readTillPrompt();
    std::vector<std::string> lines;
    boost::split(lines, resp, boost::is_any_of("\r"));

    if(lines.front() == "SEARCHING...")
        lines.erase(lines.begin());

    if(lines.front() == "NO DATA" || lines.front() == "UNABLE TO CONNECT")
        throw std::runtime_error("No data while waiting for response");

    auto newEnd = std::remove(lines.begin(), lines.end(), "");
    lines.erase(newEnd, lines.end());

    const int charToCut = 3 * bytesToCut;   //2 chars per byte + space
    if(lines.size() > 1)
    {
        for(auto& line : lines)
            line.erase(0, charToCut + 3);   //remove response header and line number
    }
    else
        lines.front().erase(0, charToCut);

    return lines;
}
