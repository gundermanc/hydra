// Project Hydra
// (C) 2016 Christian Gunderman
// Service Manager Public Interface

#include "hydra/hydra_core.h"

#include "internal/hydra_service_manager_private.h"

using namespace hydra::core;

HyAPI HyServiceManager* HyCreateServiceManager() {
    return reinterpret_cast<HyServiceManager*>(new HyServiceManagerPrivate());
}

HyAPI void HyFreeServiceManager(HyServiceManager* serviceManager) {

    // Ignore NULL serviceManager.
    if (serviceManager == NULL) {
        HyAssert(false);
        return;
    }

    delete reinterpret_cast<HyServiceManagerPrivate*>(serviceManager);
}