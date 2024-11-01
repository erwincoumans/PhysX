
#include <pybind11/pybind11.h>
#include <PxPhysicsAPI.h>

namespace py = pybind11;

void initializePhysX() {
    static physx::PxDefaultAllocator allocator;
    static physx::PxDefaultErrorCallback errorCallback;

    physx::PxFoundation* foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocator, errorCallback);
    if (!foundation) {
        throw std::runtime_error("Failed to create PhysX foundation.");
    }
    // Add additional PhysX initialization logic as needed
}

PYBIND11_MODULE(pypxim, m) {
    m.doc() = "PhysX Immediate Mode Python module";
    m.def("initialize_physx", &initializePhysX, "Initialize the PhysX SDK");
}

