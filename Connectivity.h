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

#ifndef _CONNECTIVITY_H_
#define _CONNECTIVITY_H_

#include <boost/asio/serial_port.hpp>

#include <map>
#include <string>
#include <vector>

class Elm327
{
public:
    enum Protocol
    {
        AUTO=0,
        PWM,
        VPW,
        ISO9141,
        KWP5BAUD,
        KWPFI,
        CAN11B500,
        CAN29B500,
        CAN11B250,
        CAN29B250,
        J1929CAN
    };

    static Elm327& getDevice(const std::string& device, const int baudrate = 0);


    void reset();
    void setProtocol(const Protocol proto = AUTO);
    void disableEcho();
    std::vector<std::string> sendObd(const int mode, const int pid);
    std::vector<std::string> sendObd(const int mode);

private:
    void expectOk();

    std::string readLine(const char delimiter = '\r');
    std::string readTillPrompt();

    void write(const std::string& data);
    void writeLine(const std::string& data);

    std::vector<std::string> getObdLines(const int bytesToCut);

    Elm327(const std::string& device, const int baudrate)
        :_device(device), _serial(_io, device)
    {
        _serial.set_option(boost::asio::serial_port_base::baud_rate(baudrate));
    }

    static std::map<std::string, Elm327*> _devices;

    std::string _device;
    boost::asio::io_service _io;
    boost::asio::serial_port _serial;
};

#endif
