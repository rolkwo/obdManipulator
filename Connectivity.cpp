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

    oss << std::setw(2) << std::setbase(16) << mode << pid;
    writeLine(oss.str());

    return getObdLines(2);
}

std::vector<std::string> Elm327::sendObd(const int mode)
{
    std::ostringstream oss;

    oss << std::setw(2) << std::setbase(16) << mode;
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

    if(lines.front() == "NO DATA")
        throw std::runtime_error("No data while waiting for response");

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
