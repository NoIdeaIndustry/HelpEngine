cmake_minimum_required(VERSION 3.23.1)
project(Engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall")

include_directories(include)
file(GLOB_RECURSE HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "include/*.hpp")
file(GLOB_RECURSE SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "sources/*.cpp")
add_executable(Engine sources/Main.cpp ${SOURCES} ${HEADERS})
target_link_libraries(Engine -lpthread)