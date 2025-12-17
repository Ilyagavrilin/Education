cmake_minimum_required(VERSION 3.20)
project(task_5_01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(GTest REQUIRED)

add_executable(task_5_01
    main.cc
)

target_link_libraries(task_5_01 GTest::GTest GTest::Main)
enable_testing()
gtest_discover_tests(task_5_01)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(task_5_01 PRIVATE -Wall -Wextra -Wpedantic)
elseif (MSVC)
  target_compile_options(task_5_01 PRIVATE /W4)
endif()


install(TARGETS task_5_01 RUNTIME DESTINATION bin)
