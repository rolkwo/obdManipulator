#include <Connectivity.h>

#include <iomanip>
#include <sstream>
#include <stdexcept>

#include <boost/algorithm/string.hpp>

// just for debug
#include <iostream>

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

    std::string resp = readTillPrompt();
    std::vector<std::string> lines;
    boost::split(lines, resp, boost::is_any_of("\r"));

    if(lines.front() == "SEARCHING...")
        lines.erase(lines.begin());

    return lines;
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
