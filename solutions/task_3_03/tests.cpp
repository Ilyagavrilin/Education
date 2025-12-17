#include "gtest/gtest.h"
#include "main.cpp"

TEST(ListTests, EmptyInitially) {
    List lst;
    EXPECT_TRUE(lst.empty());
}

TEST(ListTests, PushPopFrontBack) {
    List lst;
    lst.push_back(2);
    lst.push_front(1);
    lst.push_back(3);
    EXPECT_FALSE(lst.empty());
    EXPECT_EQ(lst.get(), 2);
    lst.pop_front();
    EXPECT_EQ(lst.get(), 3);
    lst.pop_back();
    lst.pop_back();
    EXPECT_TRUE(lst.empty());
}

TEST(ListTests, ShowOutput) {
    List lst;
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    EXPECT_EQ(lst.get(), 20);
}
