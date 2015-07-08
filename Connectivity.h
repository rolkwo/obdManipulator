#ifndef _CONNECTIVITY_H_
#define _CONNECTIVITY_H_

#include <boost/asio/serial_port.hpp>

#include <string>

class Elm327
{
public:
    Elm327(const std::string& device, const int baudrate)
        :_device(device), _serial(_io, device)
    {
        _serial.set_option(boost::asio::serial_port_base::baud_rate(baudrate));
    }


    void readLine(std::string& out,
                  const char delimiter = '\r');
    void readTillPrompt();
    void readTillPrompt(std::string& out);

    void write(const std::string& data);

private:
    std::string _device;
    boost::asio::io_service _io;
    boost::asio::serial_port _serial;
};

#endif
