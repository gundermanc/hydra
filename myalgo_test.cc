#include "gtest/gtest.h"

#include "myalgo.h"

TEST(MyAlgo, AddTest) {
    EXPECT_EQ(8, AddInts(3, 5));
}