// Project Hydra
// (C) 2016 Christian Gunderman
// Library Code Header

#ifndef HYDRA_CORE__H__
#define HYDRA_CORE__H__

#include "hydra/hydra_base.h"

HyAPIBlock {

// Core extensibility component for Hydra.
typedef void* HyServiceManager;

// Creates a new instance of HydraServiceManager.
HyAPI HyServiceManager* HyCreateServiceManager();

// Frees an instance of HydraServiceManager.
HyAPI void HyFreeServiceManager(HyServiceManager* serviceManager);

} // HyAPIBlock

#endif // HYDRA_CORE__H__