cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(central)

target_sources(app PRIVATE src/main.c)

FILE(GLOB app_sources src/ot/*.c)
target_include_directories(app PUBLIC src/system)
 
target_sources(app PRIVATE ${app_sources})
