cmake_minimum_required(VERSION 3.24)
project(multithreading)


find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(multithreadingNew src/main.cpp src/Fork.cpp include/Fork.h src/Philosopher.cpp include/Philosopher.h src/NcursesShower.cpp include/NcursesShower.h)
target_link_libraries(multithreadingNew ${CURSES_LIBRARIES})