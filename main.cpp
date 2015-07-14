#include <iostream>
#include <string>
#include <vector>

#include "Connectivity.h"

using namespace std;

main()
{
    try{
        Elm327& elm = Elm327::getDevice("/dev/ttyUSB0",38400);

        elm.reset();
        elm.disableEcho();
        elm.setProtocol();
        elm.sendObd(1, 0);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
