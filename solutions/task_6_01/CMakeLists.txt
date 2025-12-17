cmake_minimum_required(VERSION 3.20)
project(task_6_01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(GTest REQUIRED)

add_executable(task_6_01
    main.cc
    rational.cpp
)
target_include_directories(task_6_01 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)

target_link_libraries(task_6_01 GTest::GTest GTest::Main)
enable_testing()
gtest_discover_tests(task_6_01)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(task_6_01 PRIVATE -Wall -Wextra -Wpedantic)
elseif (MSVC)
  target_compile_options(task_6_01 PRIVATE /W4)
endif()


install(TARGETS task_6_01 RUNTIME DESTINATION bin)
