#include <gtest/gtest.h>

#define private public
#define protected public    //pls, forgive me...

#include "Connectivity.h"


namespace
{
class ConnectivityTest : public Elm327
{
public:
    ConnectivityTest()
        : Elm327("/dev/ttyUSB0", 38400)
    {
    }

    std::string read;

    std::string readTillPrompt()
    {
        return read;
    }
};

TEST(ConnectivityTest, getObdLine)
{
    ConnectivityTest con;

    con.read = "41 01 03 06 80 80\r"
               "\r";

    auto resp = con.getObdLines(2);

    EXPECT_EQ(1, resp.size());
    EXPECT_EQ("03 06 80 80", resp.front());
}


TEST(ConnectivityTest, getObdLines)
{
    ConnectivityTest con;

    con.read = "49 02 01 00 00 00 56\r"
               "49 02 02 46 31 4B 47\r"
               "49 02 03 52 45 30 35\r"
               "49 02 04 33 32 34 37\r"
               "49 02 05 32 37 38 36\r"
               "\r";

    auto resp = con.getObdLines(2);

    EXPECT_EQ(5, resp.size());
    EXPECT_EQ("00 00 00 56", resp[0]);
    EXPECT_EQ("46 31 4B 47", resp[1]);
    EXPECT_EQ("52 45 30 35", resp[2]);
    EXPECT_EQ("33 32 34 37", resp[3]);
    EXPECT_EQ("32 37 38 36", resp[4]);
}

TEST(ConnectivityTest, singleDtcLine)
{
    ConnectivityTest con;

    con.read = "43 01 00 01 00 01 10\r"
               "\r";

    auto resp = con.getObdLines(1);

    EXPECT_EQ(1, resp.size());
    EXPECT_EQ("01 00 01 00 01 10", resp.front());
}

TEST(ConnectivityTest, dtcLines)
{
    ConnectivityTest con;

    con.read = "43 01 01 00 01 00 01 10\r"
               "43 02 01 00 01 00 01 10\r"
               "\r";

    auto resp = con.getObdLines(1);

    EXPECT_EQ(2, resp.size());
    EXPECT_EQ("01 00 01 00 01 10", resp[0]);
    EXPECT_EQ("01 00 01 00 01 10", resp[1]);
}
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
