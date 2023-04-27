
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(AlphabetAstronauts)
cmake_minimum_required(VERSION 3.8)

# Suppress deprecated warnings
add_definitions(-w)

add_subdirectory(public/src ${CMAKE_BINARY_DIR}/public)
add_subdirectory(mmlplayer/ym2612 ${CMAKE_BINARY_DIR}/ym2612)
add_subdirectory(mmlplayer/mmlplayer ${CMAKE_BINARY_DIR}/mmlplayer)

add_subdirectory(src)