#include <Connectivity.h>

#include <sstream>
#include <stdexcept>

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
    std::string dummy;

    readLine(dummy);    //to read echoed ate
    expectOk();
}

void Elm327::expectOk()
{
    std::string line;
    readLine(line);

    if(line != "OK")
        throw std::runtime_error("Expected OK while response is " + line);

    readTillPrompt();
}

void Elm327::readLine(std::string& out,
                      const char delimiter)
{
    out.clear();

    char c;
    while(_serial.read_some(boost::asio::buffer(&c, 1)))
    {
        if(c == delimiter)
            break;

        out += c;
    }
}


void Elm327::readTillPrompt()
{
    char c;

    while(_serial.read_some(boost::asio::buffer(&c, 1)))
    {
        if(c == '>')
            break;
    }
}

void Elm327::readTillPrompt(std::string& out)

{
    out.clear();

    char c;

    while(_serial.read_some(boost::asio::buffer(&c, 1)))
    {
        if(c == '>')
            break;

        out += c;
    }
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
