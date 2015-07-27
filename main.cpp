// ObdManipulator - simple tool to test your car using ELM327
// Copyright (C) 2015  Roland Kwolek
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


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
