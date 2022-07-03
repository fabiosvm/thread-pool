
cmake_minimum_required(VERSION 3.0)

project(thread-pool)

file(GLOB_RECURSE sources src/*.c)

find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} ${sources})

target_link_libraries(${PROJECT_NAME} Threads::Threads)

include(CTest)

add_test(NAME thread-pool COMMAND thread-pool)
