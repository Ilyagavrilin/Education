cmake_minimum_required(VERSION 3.20)
project(task_3_03 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(GTest REQUIRED)
add_executable(task_3_03 main.cpp)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(task_3_03 PRIVATE -Wall -Wextra -Wpedantic)
elseif (MSVC)
  target_compile_options(task_3_03 PRIVATE /W4)
endif()



target_link_libraries(task_3_03 GTest::GTest GTest::Main)
enable_testing()
gtest_discover_tests(task_3_03)

install(TARGETS task_3_03 RUNTIME DESTINATION bin)