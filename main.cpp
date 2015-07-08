#include <iostream>
#include <string>
#include <vector>

#include "Connectivity.h"

using namespace std;

main()
{
    try{
        Elm327 elm("/dev/ttyS0", 115200);
        elm.write("atz\r");


        elm.readTillPrompt();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
