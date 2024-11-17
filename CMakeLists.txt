cmake_minimum_required(VERSION 3.16) 
project(main)

# include(FetchContent)

SET (CMAKE_CXX_COMPILER             "clang++-15")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ".")


SET (CMAKE_AR      "/usr/bin/llvm-ar")
SET (CMAKE_LINKER  "/usr/bin/llvm-ld")
SET (CMAKE_NM      "/usr/bin/llvm-nm")
SET (CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
SET (CMAKE_RANLIB  "/usr/bin/llvm-ranlib")


SET(CMAKE_CXX_FLAGS "-O0")
SET(CMAKE_CXX_FLAGS "-g")

# find_package(Threads REQUIRED) # for pthread
find_package(fmt CONFIG REQUIRED)
include_directories(include)

file(GLOB MAIN "main.cpp")

add_executable(main ${MAIN})

target_link_libraries(main 
  PRIVATE 
    # gtest_main 
    fmt::fmt
    # Threads::Threads
)

