cmake_minimum_required (VERSION 3.0)

PROJECT (HELMET)

set(CMAKE_BUILD_TYPE Debug)

include_directories(include)

set (CMAKE_MODULE_PATH "/home/pi/Pi0W")

file (GLOB SOURCES "src/*.c" "src/*.h")

set ( GCC_COVERAGE_LINK_FLAGS "-lbluetooth  -lpthread")
set ( CMAKE_EXE_LINKER_FLAGS "${GCC_COVERAGE_LINK_FLAGS}")

add_executable (Helmet ${SOURCES})

find_package( Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})
find_package(ALSA REQUIRED)
include_directories(${ALSA_INCLUDE_DIRS})
target_link_libraries(Helmet ${CURSES_LIBRARIES} ${ALSA_LIBRARY} )

