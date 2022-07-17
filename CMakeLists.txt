cmake_minimum_required(VERSION 3.19)
project(Design)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC
       ${PROJECT_SOURCE_DIR}/*.cpp
       ${PROJECT_SOURCE_DIR}/*.h
       ${PROJECT_SOURCE_DIR}/Reactor/*.cpp
       ${PROJECT_SOURCE_DIR}/Reactor/*.h)

#打印SRC中列表信息
message(STATUS "SRC = ${SRC}")

add_executable(${PROJECT_NAME} ${SRC})
