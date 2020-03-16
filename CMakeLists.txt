cmake_minimum_required(VERSION 3.1)

#set config
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../bin")
set(CMAKE_CXX_STANDARD 17)

project(RSG VERSION 0.1)

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

SET(CURSES_USE_NCURSES TRUE)
find_package(Curses REQUIRED)


include_directories(include)
include_directories(libarys)

file(GLOB SOURCES "src/*.cpp")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
add_executable(rsg-test ${SOURCES})
target_link_libraries(rsg-test ${CMAKE_THREAD_LIBS_INIT} ${CURSES_LIBRARIES})
else()
add_executable(rsg ${SOURCES})
target_link_libraries(rsg ${CMAKE_THREAD_LIBS_INIT} ${CURSES_LIBRARIES})
endif()
