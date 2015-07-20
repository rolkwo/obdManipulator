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
    EXPECT_FALSE(Utils::checkPidSupport("", 1, 16));
    EXPECT_TRUE(Utils::checkPidSupport("", 1, 21));
    EXPECT_FALSE(Utils::checkPidSupport("", 1, 36));
}

}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
