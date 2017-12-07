cmake_minimum_required (VERSION 3.0)

PROJECT (BIKE)

file (GLOB SOURCES "src/*.c" "src/*.h")

add_executable (Bike ${SOURCES})
