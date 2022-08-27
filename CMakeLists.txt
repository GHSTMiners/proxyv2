cmake_minimum_required(VERSION 3.10)

# Set the project name
project(proxy)

# Find libraries
find_package(spdlog REQUIRED)

# fetch latest argparse
include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

FetchContent_Declare(
    IXWebSocket
    GIT_REPOSITORY https://github.com/machinezone/IXWebSocket.git
)
FetchContent_MakeAvailable(IXWebSocket)

# Add source files
set(SOURCE_FILES main.cpp Bootstrapper/Bootstrapper.cpp Settings/Settings.cpp Proxy/Proxy.cpp)

# Create the executable
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

# Add include directory
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Link include directories, libraries, defines etc.
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ixwebsocket argparse spdlog)