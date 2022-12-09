set(APP_NAME DemoApp)

project(${APP_NAME} LANGUAGES CXX)

cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

set(DEMO_SRC ${CMAKE_SOURCE_DIR}/../demo_app)

add_library(vehicles SHARED
    ${DEMO_SRC}/vehicles.cpp
    ${DEMO_SRC}/vehicles.hpp
)

add_library(machines SHARED
    ${DEMO_SRC}/machines.cpp
    ${DEMO_SRC}/machines.hpp
)

add_library(robots SHARED
    ${DEMO_SRC}/robots.cpp
    ${DEMO_SRC}/robots.hpp
)

target_link_libraries(machines robots)


add_executable(${APP_NAME} MACOSX_BUNDLE ${DEMO_SRC}/main.cpp)

set_target_properties(${APP_NAME} PROPERTIES
    BUNDLE True
    MACOSX_BUNDLE_GUI_IDENTIFIER org.me.${APP_NAME} 
    MACOSX_BUNDLE_BUNDLE_NAME ${APP_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION "0.1"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1"
    #MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/cmake/customtemplate.plist.in
)

target_link_libraries(${APP_NAME} vehicles machines)
