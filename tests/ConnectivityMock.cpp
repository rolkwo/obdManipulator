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
