#include <iostream>
#include <string>
#include <vector>

#include <boost/asio/serial_port.hpp>
#include <boost/asio/read.hpp>

using namespace std;
using namespace boost::asio;

void readLine(boost::asio::serial_port& serial,
        std::string& out,
        const char delimiter = '\r')
{
    char c;
    while(serial.read_some(boost::asio::buffer(&c, 1)))
    {
        if(c == delimiter)
            break;

        out += c;
    }
}

void readTillPrompt(boost::asio::serial_port& serial)
{
    char c;

    while(serial.read_some(boost::asio::buffer(&c, 1)))
    {
        if(c == '>')
            break;
    }
}

main()
{
    try{
        io_service io;
        serial_port serial(io, "/dev/ttyUSB0");
        std::cout << serial.is_open() << std::endl;
        serial.set_option(serial_port_base::baud_rate(38400));
//        serial.set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));
//        serial.set_option(serial_port_base::parity(serial_port_base::parity::none));
//        serial.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));
//        serial.set_option(serial_port_base::character_size(8));
        serial.write_some(buffer("atz\r"));

//        string line;
//        readLine(serial, line);
//        cout << line << endl;
//
//        line.clear();
//        readLine(serial, line);
//        cout << line << endl;
//
//        line.clear();
//        readLine(serial, line);
//        cout << line << endl;
//
//        line.clear();
//        readLine(serial, line);
//        cout << line << endl;
//
//        line.clear();
//        readLine(serial, line);
//        cout << line << endl;

        readTillPrompt(serial);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
