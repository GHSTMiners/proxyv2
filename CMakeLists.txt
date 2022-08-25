cmake_minimum_required(VERSION 3.10)

# Set the project name
project(proxy)

# Find libraries
find_package(spdlog REQUIRED)
find_package(websocketpp REQUIRED)
FIND_PACKAGE(Boost REQUIRED COMPONENTS system thread )
# fetch latest argparse
include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

# Add source files
set(SOURCE_FILES main.cpp Bootstrapper/Bootstrapper.cpp Settings/Settings.cpp)

# Create the executable
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

# Add include directory
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Link include directories, libraries, defines etc.
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC websocketpp::websocketpp ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} argparse spdlog)