cmake_minimum_required(VERSION 3.20)
project(task_3_03 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(task_3_03
    main.cpp
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(task_3_03 PRIVATE -Wall -Wextra -Wpedantic)
elseif (MSVC)
  target_compile_options(task_3_03 PRIVATE /W4)
endif()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(test_03_03 main.cpp tests.cpp)
target_link_libraries(test_03_03 PRIVATE gtest_main)
enable_testing()
add_test(NAME ListTests COMMAND test_03_03)

install(TARGETS task_3_03 RUNTIME DESTINATION bin)