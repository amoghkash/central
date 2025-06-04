cmake_minimum_required(VERSION 3.20.0)

# Include Zephyr boilerplate
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(central)

# Add source files
# target_sources(app PRIVATE
#     src/main.c
#     src/ot/mesh.c
#     src/ot/handler.c
#     src/utils/peripherals.c
# )

target_include_directories(app PUBLIC src/system)
target_include_directories(app PRIVATE src/include)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
target_sources(app PRIVATE ${SOURCES})

