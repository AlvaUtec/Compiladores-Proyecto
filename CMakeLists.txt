cmake_minimum_required(VERSION 3.25)
project(proyecto)

set(CMAKE_CXX_STANDARD 17)
# Collect source and header files
file(GLOB SOURCES "codigo/*.cpp")
file(GLOB HEADERS "codigo/*.hh")

# svm
file(GLOB SOURCES1 "codigo/svm/*.cpp")
file(GLOB HEADERS2 "codigo/svm/*.hh")
add_executable(proyecto ${SOURCES} ${HEADERS})
add_executable(proyecto_svm ${SOURCES1} ${HEADERS2})
