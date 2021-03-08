cmake_minimum_required(VERSION 3.1.0)
project(chess960generator VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(chess960generator 
        test/main.cpp
        src/c960generator.cpp
)

include_directories(src)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
