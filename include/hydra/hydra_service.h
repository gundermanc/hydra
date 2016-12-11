// Project Hydra
// (C) 2016 Christian Gunderman
// Base Defines

#ifndef HYDRA_SERVICE__H__
#define HYDRA_SERVICE__H__

#include <string>

#include "hydra_base.h"

// Hydra Service C ABI. Do not use these structs, use the C++ templates.

HyAPIBlock {

const int kMaxServiceId = 255;

typedef HyPtr HyServiceState;

enum HyServiceLifetimePolicy {
    HyServiceLifetimeDefault,
    HyServiceLifetimeNoAlloc
};

typedef struct __HyServiceLifecycle {
    HyPtr data = nullptr;
    void(*Alloc)() = nullptr;
    void(*Free)() = nullptr;
};

typedef struct __HyServiceDefinition {
public:
    __HyServiceDefinition(
        const HyChar* const interfaceId,
        const HyChar* const serviceId,
        HyServiceLifetimePolicy lifetimePolicy,
        const HyPtr implementation,
        const HySize implementationSize) :
        _interfaceId(interfaceId),
        _serviceId(serviceId),
        _lifetimePolicy(lifetimePolicy),
        _implementation(implementation),
        _implementationSize(implementationSize) { }

protected:
    const HyChar* const _interfaceId;
    const HyChar* const _serviceId;
    const HyServiceLifetimePolicy _lifetimePolicy;
    const HyPtr _implementation;
    const HySize _implementationSize;
};

} // HyAPIBlock


// C++ wrapper classes. These wrapper classes allow us to cleanly use
// functionality with a C ABI, but C++ style syntactic sugar and compile
// time guarantees.

template <typename TInterface>
class HyInterfaceDefinition {
public:
    HyInterfaceDefinition(const HyChar* const interfaceId) : _interfaceId(interfaceId) {
        static_assert(std::is_pointer<TInterface>::value, "Hydra interface must be pointer");

        HyAssertValidServiceId(interfaceId);
    }

    const HyChar* const InterfaceId() const { return this->_interfaceId; }

private:
    const HyChar* const _interfaceId;
};

template <typename TInterface>
class HyServiceDefinition : private __HyServiceDefinition {
public:
    HyServiceDefinition(
        const HyInterfaceDefinition<TInterface>* interfaceDef,
        const HyChar* const serviceId,
        HyServiceLifetimePolicy lifetimePolicy,
        TInterface implementation) :
        __HyServiceDefinition(
            interfaceDef->InterfaceId(),
            serviceId,
            lifetimePolicy,
            static_cast<HyPtr>(implementation),
            sizeof(TInterface)) {

        HyAssertValidServiceId(serviceId);
    }

    HyChar* InterfaceId() { return this->interfaceId; }
    HyChar* ServiceId() { return this->serviceId; }
    HyServiceLifetimePolicy LifetimePolicy() { return this->_lifetimePolicy; }
    const TInterface const Implementation() { return (TInterface)(this->_implementation); }
};

#define HyDeclareInterface(name, id, members)                       \
typedef struct name {                                               \
    __HyServiceLifecycle lifecycle;                                 \
    members                                                         \
};                                                                  \
const HyInterfaceDefinition< name *> __ ## name(id);

#define HyDeclareImplementation(iface, name, members)               \
iface __ ## name = { __HyServiceLifecycle(), members };

static inline void HyAssertValidServiceId(const HyChar* serviceId) {
    HyAssert(serviceId != nullptr);
    HyAssert(strlen(serviceId) > 0);
    HyAssert(strlen(serviceId) < kMaxServiceId);
}

#define HyDeclareServiceImplementation(iface, name, id, lifetime, ...)     \
HyDeclareImplementation(                                                   \
    iface,                                                                 \
    name,                                                                  \
    __VA_ARGS__);                                                          \
HyServiceDefinition< iface *> name(                                  \
    &__ ## iface,                                                          \
    id,                                                                    \
    lifetime,                                                              \
    &__ ## name);

#endif // HYDRA_SERVICE__H__