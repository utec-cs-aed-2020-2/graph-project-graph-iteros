CMAKE_MINIMUM_REQUIRED(VERSION 3.17)

project(graph-project-graph-iteros)

file(GLOB SOURCES "main.cpp" "Graph/*")

add_executable(graph-project-graph-iteros ${SOURCES})