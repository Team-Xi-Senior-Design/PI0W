cmake_minimum_required (VERSION 3.0)

PROJECT (HELMET)

file (GLOB SOURCES "src/*.c" "src/*.h")

add_executable (Helmet ${SOURCES})

set ( GCC_COVERAGE_LINK_FLAGS "-lbluetooth")
set ( CMAKE_EXE_LINKER_FLAGS "${GCC_COVERAGE_LINK_FLAGS}")

find_package( Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})
find_package(ALSA REQUIRED)
include_directories(${ALSA_INCLUDE_DIRS})
target_link_libraries(Helmet ${CURSES_LIBRARIES} ${ALSA_LIBRARY} )
