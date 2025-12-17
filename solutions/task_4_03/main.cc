#include <cassert>
#include <concepts>
#include <string>
#include <vector>
#include <gtest/gtest.h>

template<typename Container>
concept HasPushBack = requires(Container c, int value) {
    { c.push_back(value) } -> std::same_as<void>;
};

template<HasPushBack Container>
void handle(Container& container, int value) {
    container.push_back(value);
}

template<HasPushBack Container, typename T>
void handle(Container&, T) {}

template<HasPushBack Container, typename... Args>
void insert_ints(Container& container, Args... args) {
    (handle(container, args), ...);
}

TEST(InsertIntsTest, OnlyIntegers) {
    std::vector<int> v;
    insert_ints(v, 1, 2, 3, 4, 5);
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
    EXPECT_EQ(v[4], 5);
}

TEST(InsertIntsTest, MixedTypes) {
    std::vector<int> v;
    insert_ints(v, 10, 3.14, 20, "hello", 30, 'c', 40);
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);
    EXPECT_EQ(v[3], 40);
}

TEST(InsertIntsTest, EmptyPack) {
    std::vector<int> v;
    insert_ints(v);
    EXPECT_TRUE(v.empty());
}

TEST(InsertIntsTest, ComplexMixedTypes) {
    std::vector<int> v;
    std::string s = "test";
    double d = 2.718;
    insert_ints(v, 1, s, 2, d, 3, 'a', 4);
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
