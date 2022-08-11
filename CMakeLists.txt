cmake_minimum_required(VERSION 3.10)

# Set the project name
project(proxy)

# Find libraries
find_package(websocketpp REQUIRED)
FIND_PACKAGE(Boost REQUIRED COMPONENTS system thread )

# Add source files
set(SOURCE_FILES main.cpp)

# Create the executable
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

# Link include directories, libraries, defines etc.
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC websocketpp::websocketpp ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY})