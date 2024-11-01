cmake_minimum_required(VERSION 3.12)
project(pybind11_example)

include(FetchContent)

# Download pybind11 if not already present
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG        v2.11.1  # Use the appropriate version
)
FetchContent_MakeAvailable(pybind11)

# Include pybind11
#find_package(pybind11 REQUIRED)


# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories for PhysX
include_directories(../physx/include)

# Specify the paths to the pre-built PhysX static libraries
link_directories(../physx/bin/linux.clang/release)


# Link your module against the PhysX libraries
pybind11_add_module(pypxim src/pypxim.cpp)
target_link_libraries(pypxim
    PRIVATE
    libPhysXFoundation_static_64.a
    libPhysXPvdSDK_static_64.a
    libPhysX_static_64.a
    libPhysXCommon_static_64.a
    libPhysXExtensions_static_64.a
)

