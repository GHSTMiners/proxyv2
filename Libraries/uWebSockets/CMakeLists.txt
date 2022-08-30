cmake_minimum_required(VERSION 3.10)

# Set the project name
project(uWebSockets)

# Find libraries
find_package(OpenSSL REQUIRED)

# Add source files
file(GLOB_RECURSE SOURCE_FILES repo/src/*.h)

# Create the executable
add_library(${PROJECT_NAME} INTERFACE)

# Compile time definitions
add_definitions(${PROJECT_NAME} PUBLIC LIBUS_USE_OPENSSL=1)
add_definitions(${PROJECT_NAME} PUBLIC LIBUS_USE_ASIO=1)

# Add include directory
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/repo/src)

# Link include directories, libraries, defines etc.
target_link_libraries(${PROJECT_NAME} INTERFACE OpenSSL::SSL uSockets)
