#ifndef _DATATRANSLATOR_H_
#define _DATATRANSLATOR_H_

#include "Connectivity.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

class Getter
{
public:
    virtual std::vector<std::string> getPid(const int pid) = 0;
};

class CurrentGetter : public Getter
{
public:
    CurrentGetter(const std::string& dev);
    virtual std::vector<std::string> getPid(const int pid) override;

private:
    Elm327& _dev;
};

class FreezeFrameGetter : public Getter
{
public:
    FreezeFrameGetter(const std::string& dev);
    virtual std::vector<std::string> getPid(const int pid) override;

private:
    Elm327& _dev;
};


class DataTranslator
{
public:
    DataTranslator(std::shared_ptr<Getter> getter);
    std::string fuelSystemStatus();
    std::string calculatedEngineLoad();
    std::string engineCoolantTemperature();
    std::string shortTermFuelTrimBank1();
    std::string longTermFuelTrimBank1();
    std::string shortTermFuelTrimBank2();
    std::string longTermFuelTrimBank2();

private:
    std::vector<uint8_t> prepareBytes(const std::string& hexString);
    std::vector<uint8_t> prepareBytes(const std::vector<std::string>& lines);

    std::shared_ptr<Getter> _getter;
};

#endif
