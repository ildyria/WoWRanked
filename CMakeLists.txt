cmake_minimum_required(VERSION 3.6)
project(WoWMC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pedantic -O3 -Wall -Wextra")

set(SOURCE_FILES
        tools/random.cpp
    tools/random.h
    tools/timer.h
    main.cpp
    Makefile
    README.md Rank.h Progress.h)

add_executable(WoWMC ${SOURCE_FILES})