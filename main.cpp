#include <iostream>
#include <string>
#include <vector>

#include <boost/asio/serial_port.hpp>

using namespace std;
using namespace boost::asio;

main()
{
    try{
        io_service io;
        serial_port serial(io, "/dev/ttyUSB6");
        std::cout << serial.is_open() << std::endl;
        serial.set_option(serial_port_base::baud_rate(115200));
        serial.write_some(buffer("atz\n"));

        sleep(1);
        char c;
        std::vector<char> buf;
        serial.read_some(buffer(buf, 10));

        std::string resp(buf.begin(), buf.end());
        std::cout << resp << std::endl;
        std::cout << buf.size() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
