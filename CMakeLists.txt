cmake_minimum_required(VERSION 3.10)

# Set the project name
project(proxy)

# Find libraries)
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)

# fetch latest argparse
include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
    GIT_TAG v2.6
)
FetchContent_MakeAvailable(argparse)

add_subdirectory(Libraries/uSockets)
add_subdirectory(Libraries/uWebSockets)

# Add source files
set(SOURCE_FILES main.cpp Bootstrapper/Bootstrapper.cpp Settings/Settings.cpp Proxy/Proxy.cpp ServerPool/ServerPool.cpp)

# Create the executable
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

# Add include directory
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Link include directories, libraries, defines etc.
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC argparse spdlog fmt uWebSockets uSockets ${Boost_LIBRARIES} hiredis)