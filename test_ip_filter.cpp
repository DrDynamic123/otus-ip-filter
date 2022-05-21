#define TEST_MODULE test_ip_filter

#include "gtest/gtest.h"

#include "ip_address.h"
#include "ip_filter.h"


TEST(IpAddress_test, toString)
{
    std::string strIp1 = "1.2.3.4";
    EXPECT_EQ(IpAddress(strIp1).toString(), strIp1);
    std::string strIp2 = "12.34.56.78";
    EXPECT_EQ(IpAddress(strIp2).toString(), strIp2);
    std::string strIp3 = "123.456.789.123";
    EXPECT_EQ(IpAddress(strIp3).toString(), strIp3);
    std::string strIp4 = "1.23.345.6";
    EXPECT_EQ(IpAddress(strIp4).toString(), strIp4);
    std::string strIp5 = "0.0.0.0";
    EXPECT_EQ(IpAddress(strIp5).toString(), strIp5);
}

TEST(IpAddress_test, get)
{
    std::array<int, 4> arrIp0 = {0,0,0,0};
    EXPECT_EQ(IpAddress().get(), arrIp0);
    EXPECT_EQ(IpAddress("0.0.0.0").get(), arrIp0);

    std::array<int, 4> arrIp1 = {1,2,3,4};
    EXPECT_EQ(IpAddress("1.2.3.4").get(), arrIp1);
}

TEST(IpAddress_test, contain)
{
    EXPECT_TRUE(IpAddress("1.2.3.4").contain(1));
    EXPECT_TRUE(IpAddress("12.34.56.78").contain(56));
    EXPECT_FALSE(IpAddress("1.2.3.4").contain(0));
    EXPECT_FALSE(IpAddress("12.34.56.78").contain(11));
}

TEST(IpAddress_test, operator_greater)
{
    EXPECT_TRUE(IpAddress("1.10.1.1") > IpAddress("1.2.1.1"));
    EXPECT_FALSE(IpAddress("1.10.1.1") > IpAddress("1.10.1.1"));
    EXPECT_FALSE(IpAddress("1.2.1.1") > IpAddress("1.10.1.1"));
}

TEST(ip_filter_test, filter)
{
    std::vector<IpAddress> ip_pool;
    ip_pool.reserve(6);
    ip_pool.emplace_back("5.8.47.202");
    ip_pool.emplace_back("5.8.69.43");
    ip_pool.emplace_back("5.13.73.104");
    ip_pool.emplace_back("14.162.206.233");
    ip_pool.emplace_back("1.231.69.33");
    ip_pool.emplace_back("69.23.42.183");

    std::string ip_5;
    for(const auto &ip : filter(ip_pool, 5))
    {
        if (!ip_5.empty())
            ip_5.append(" ");
        ip_5.append(ip.toString());
    }
    EXPECT_EQ(ip_5, "5.8.47.202 5.8.69.43 5.13.73.104");

    std::string ip_5_8;
    for(const auto &ip : filter(ip_pool, 5, 8))
    {
        if (!ip_5_8.empty())
            ip_5_8.append(" ");
        ip_5_8.append(ip.toString());
    }
    EXPECT_EQ(ip_5_8, "5.8.47.202 5.8.69.43");
}

TEST(ip_filter_test, filter_any)
{
    std::vector<IpAddress> ip_pool;
    ip_pool.reserve(6);
    ip_pool.emplace_back("5.8.47.202");
    ip_pool.emplace_back("5.8.69.43");
    ip_pool.emplace_back("5.13.73.104");
    ip_pool.emplace_back("14.162.206.233");
    ip_pool.emplace_back("1.231.69.33");
    ip_pool.emplace_back("69.23.42.183");

    std::string ip_any_69;
    for(const auto &ip : filter_any(ip_pool, 69))
    {
        if (!ip_any_69.empty())
            ip_any_69.append(" ");
        ip_any_69.append(ip.toString());
    }

    EXPECT_EQ(ip_any_69, "5.8.69.43 1.231.69.33 69.23.42.183");
}
