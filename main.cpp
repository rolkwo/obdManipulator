#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Connectivity.h"
#include "DataTranslator.h"
#include "DtcHandler.h"
#include "VechicleInfoHandler.h"
#include "Utils.h"

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

        VechicleInfoHandler vechicleInfo("/dev/ttyUSB0");
        std::string vin = vechicleInfo.getVin();

        std::cout << "VIN: " << vin << std::endl;

        DataTranslator curTranslator(std::make_shared<CurrentGetter>("/dev/ttyUSB0"));

        std::cout << "Coolant temp " << curTranslator.engineCoolantTemperature() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
