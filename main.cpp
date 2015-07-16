#include <iostream>
#include <string>
#include <vector>

#include "Connectivity.h"
#include "DtcHandler.h"

using namespace std;

int main()
{
    try{
        Elm327& elm = Elm327::getDevice("/dev/ttyUSB0",38400);

        elm.reset();
        elm.disableEcho();
        elm.setProtocol();

        DtcHandler dtcHandler("/dev/ttyUSB0");
        auto codes = dtcHandler.getCodes();

        for(const auto& code : codes)
            std::cout << code << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
