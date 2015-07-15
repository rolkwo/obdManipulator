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
