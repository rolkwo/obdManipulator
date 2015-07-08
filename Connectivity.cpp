#include <Connectivity.h>


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
