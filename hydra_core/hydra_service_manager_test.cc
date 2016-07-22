// Project Hydra
// (C) 2016 Christian Gunderman
// Library Code Tests

#include "gtest/gtest.h"

#include "hydra/hydra_core.h"

// Checks for allocation on HyCreateServiceManager() and no crash
// on HyFreeServiceManager.
TEST(HydraCoreServiceManager, HyCreateFreeServiceManager) {
    HyServiceManager* serviceManager = HyCreateServiceManager();

    EXPECT_TRUE(serviceManager != NULL);

    HyFreeServiceManager(serviceManager);
}