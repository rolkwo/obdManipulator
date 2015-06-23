#include <iostream>
#include <string>
#include <vector>

#include <boost/asio/serial_port.hpp>
#include <boost/asio/read.hpp>

using namespace std;
using namespace boost::asio;

void readLine(boost::asio::serial_port& serial,
        std::string& out,
        const char delimiter = '\n')
{
    char c;
    while(serial.read_some(boost::asio::buffer(&c, 1)))
    {
        if(c == delimiter)
            break;

        out += c;
    }
}

main()
{
    try{
        io_service io;
        serial_port serial(io, "/dev/ttyS0");
        std::cout << serial.is_open() << std::endl;
        serial.set_option(serial_port_base::baud_rate(115200));
//        serial.set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));
//        serial.set_option(serial_port_base::parity(serial_port_base::parity::none));
//        serial.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));
//        serial.set_option(serial_port_base::character_size(8));
        serial.write_some(buffer("ls\n"));

        string line;
        readLine(serial, line);
        cout << line << endl;

        readLine(serial, line);
        cout << line << endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
