cmake_minimum_required(VERSION 3.1)

#set config
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")
set(CMAKE_CXX_STANDARD 17)

project(RSG VERSION 0.1)

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

SET(CURSES_USE_NCURSES TRUE)
find_package(Curses QUIET)


include_directories(include)
include_directories(libarys)

file(GLOB SOURCES "src/*.cpp")

file(GLOB COMMON "src/common/*.cpp")
file(GLOB NCURCES "src/ncurces-interface/*.cpp")
file(GLOB CMD "src/cmd-interface/*.cpp")

add_library(RSG ${COMMON})

add_executable(rsg-test ${CMD})
target_link_libraries(rsg-test ${CMAKE_THREAD_LIBS_INIT} RSG)

add_executable(rsg-cmd ${CMD})
target_link_libraries(rsg-cmd ${CMAKE_THREAD_LIBS_INIT} RSG)

if(NOT CURSES_LIBRARIES)
message(STATUS "NCURCES not found not compiling the ncurces gui")
else()
add_executable(rsg-ncurces ${NCURCES})
target_link_libraries(rsg-ncurces ${CMAKE_THREAD_LIBS_INIT} ${CURSES_LIBRARIES} RSG)
install(TARGETS rsg-ncurces DESTINATION bin)
endif()

install(TARGETS RSG  DESTINATION lib)
install(FILES include/RSG.hpp DESTINATION include)
install(TARGETS rsg-cmd DESTINATION bin)
