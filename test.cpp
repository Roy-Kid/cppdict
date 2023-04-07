#include <gtest/gtest.h>
#include "dict.h"
#include <variant>

TEST(TestData, test_init)
{
    Data<int, std::string> data;
    data.set(1);
    EXPECT_EQ(data.get<int>(), 1);
    data.set("hello");
    EXPECT_EQ(data.get<std::string>(), "hello");

    Data<int, std::string> data1(1);
    EXPECT_EQ(data1.get<int>(), 1);

    Data<int, std::string> data2("hello");
    EXPECT_EQ(data2.get<std::string>(), "hello");

}

TEST(TestData, test_is)
{

    Data<int, std::string> data;
    data.set(1);
    EXPECT_TRUE(data.is<int>());
    EXPECT_FALSE(data.is<std::string>());

}

TEST(TestData, test_eq)
{

    Data<int, std::string> data1(1);
    Data<int, std::string> data2(1);
    EXPECT_TRUE(data1 == data2);

    Data<int, std::string> data3("hello");
    Data<int, std::string> data4("hello");
    EXPECT_TRUE(data3 == data4);

    Data<int, std::string> data5(1);
    Data<int, std::string> data6("hello");
    EXPECT_FALSE(data5 == data6);

    std::variant<int, double> v1(1);
    std::variant<int, double> v2(1.0);
    EXPECT_FALSE(v1 == v2);

    Data<int, double> data7(1);
    Data<int, double> data8(1.0);
    EXPECT_FALSE(data7 == data8);
}

TEST(TestData, test_property)
{
    Data<int, double, std::string> data(1);
    auto index = data.index();
}

TEST(TestDict, test1)
{

    Dict<int, std::string> dict;
    dict["a"] = 1;
    dict["b"] = "hello";

    EXPECT_EQ(dict["a"].get<int>(), 1);
    EXPECT_EQ(dict["b"].get<std::string>(), "hello");

}