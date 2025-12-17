cmake_minimum_required(VERSION 3.20)
project(task_2_09 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(task_2_09
    main.cpp
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(task_2_09 PRIVATE -Wall -Wextra -Wpedantic)
elseif (MSVC)
  target_compile_options(task_2_09 PRIVATE /W4)
endif()

install(TARGETS task_2_09 RUNTIME DESTINATION bin)