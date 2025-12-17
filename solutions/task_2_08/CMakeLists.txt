cmake_minimum_required(VERSION 3.20)
project(task_2_08 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(task_2_08
    main.cc
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(task_2_08 PRIVATE -Wall -Wextra -Wpedantic)
elseif (MSVC)
  target_compile_options(task_2_08 PRIVATE /W4)
endif()

install(TARGETS task_2_08 RUNTIME DESTINATION bin)
