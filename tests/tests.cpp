#include "DataTranslator.h"
#include "DtcHandler.h"
#include "VechicleInfoHandler.h"
#include "Utils.h"

#include "gtest/gtest.h"

namespace
{
class VechicleInfoHandlerTest : public ::testing::Test,
                                public VechicleInfoHandler
{
public:
    VechicleInfoHandlerTest()
    : VechicleInfoHandler("/dev/ttyUSB0")
    {
    }
};

TEST_F(VechicleInfoHandlerTest, vinParsing)
{
    std::vector<std::string> lines = {"00 00 00 31",
                                      "44 34 47 50",
                                      "30 30 52 35",
                                      "35 42 31 32",
                                      "33 34 35 36"};

    EXPECT_EQ("1D4GP00R55B123456", processLines(lines));
}

TEST(Utils, getAvailablePids)
{
    EXPECT_TRUE(Utils::checkPidSupport("", 1, 1));
    EXPECT_FALSE(Utils::checkPidSupport("", 1, 18));
    EXPECT_TRUE(Utils::checkPidSupport("", 1, 32));
    EXPECT_FALSE(Utils::checkPidSupport("", 1, 22));
}

TEST(Dtc, getDtc)
{
    DtcHandler dtcHandler("mock");

    auto dtcs = dtcHandler.getCodes();
    EXPECT_EQ(1, dtcs.size());
    EXPECT_EQ("P0133", dtcs.front().code);
}

class FakeGetter : public Getter
{
public:
    virtual std::vector<std::string> getPid(const int pid) override
    {
        return _toReturn;
    }

    std::vector<std::string> _toReturn;
};

TEST(DataTranslator, engineCoolantTemperature)
{
    auto getter = std::make_shared<FakeGetter>();

    getter->_toReturn.push_back("32");

    DataTranslator translator(getter);

    EXPECT_EQ("10 Celsius degrees", translator.engineCoolantTemperature());
}

TEST(DataTranslator, calculatedEngineLoad)
{
    auto getter = std::make_shared<FakeGetter>();

    getter->_toReturn.push_back("50");

    DataTranslator translator(getter);

    EXPECT_EQ("31%", translator.calculatedEngineLoad());
}

TEST(DataTranslator, shortTermFuelTrimBank1)
{
    auto getter = std::make_shared<FakeGetter>();

    getter->_toReturn.push_back("F0");

    DataTranslator translator(getter);

    EXPECT_EQ("87%", translator.shortTermFuelTrimBank1());
}

}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
