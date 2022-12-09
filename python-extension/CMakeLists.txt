cmake_minimum_required(VERSION 3.19)

set(APP_NAME complex)

project(${APP_NAME} LANGUAGES C)

set(CMAKE_C_STANDARD 11)

set(HOME $ENV{HOME})

set(EXTENSION ${APP_NAME})

find_package(Python COMPONENTS Interpreter Development)

message("python:" ${Python_EXECUTABLE})
message("python_include" ${Python_INCLUDE_DIRS})

message("PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR})
message("CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR})


# uncomment for output in ${CMAKE_SOURCE_DIR}
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

Python_add_library(${EXTENSION} MODULE
    ${CMAKE_SOURCE_DIR}/complex.c
)

set_target_properties(${EXTENSION}
    PROPERTIES
    PREFIX ""
    SUFFIX ".so"
)

target_include_directories(${EXTENSION} PUBLIC
    ${Python_INCLUDE_DIRS}
    /usr/local/include
    ${CMAKE_SOURCE_DIR}
)

target_compile_options(${EXTENSION} PUBLIC
    "-Wno-unused-result"
    "-Wsign-compare"
    "-Wunreachable-code"
    "-DNDEBUG"
    "-g"
    "-fwrapv"
    "-O3"
    "-Wall"
)

target_link_options(${EXTENSION} PUBLIC
    "-undefined"
    "dynamic_lookup"
    "-Wno-unused-result"
    "-Wsign-compare"
    "-Wunreachable-code"
    "-fno-common"
    "-dynamic"
)

