// Project Hydra
// (C) 2016 Christian Gunderman
// Library Code Tests

#include "gtest/gtest.h"

#include "hydra/hydra_core.h"

TEST(HydraCore, AddTest) {
    EXPECT_EQ(8, AddInts(3, 5));
}