#ifndef _UTILS_H_
#define _UTILS_H_

#include <cstdint>
#include <string>
#include <vector>

class Utils
{
public:
    static bool checkPidSupport(const std::string& dev, const int mode, const int pid);
    static std::string hexStrToStr(const std::string& hexStr);
    static void removeSpaces(std::string& str);
    static std::vector<uint8_t> hexStrToByteArray(const std::string& hexStr);

};

#endif
