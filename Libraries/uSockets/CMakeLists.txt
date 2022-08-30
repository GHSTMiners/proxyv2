cmake_minimum_required(VERSION 3.10)

# Set the project name
project(uSockets C)

# Find libraries
find_package(OpenSSL REQUIRED)

# Add source files
file(GLOB_RECURSE SOURCE_FILES repo/src/*.c repo/src/*.cpp)

# Create the executable
add_library(${PROJECT_NAME} ${SOURCE_FILES})

# Compile time definitions
target_compile_definitions(${PROJECT_NAME} PUBLIC LIBUS_USE_OPENSSL=1)
target_compile_definitions(${PROJECT_NAME} PUBLIC LIBUS_USE_ASIO=1)

# Add include directory
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/repo/src)

# Link include directories, libraries, defines etc.
target_link_libraries(${PROJECT_NAME} PUBLIC OpenSSL::SSL)
