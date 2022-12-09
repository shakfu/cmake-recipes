set(APP_NAME DemoApp)

project(${APP_NAME} LANGUAGES CXX)

cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

string(REPLACE "-O3" "-O2" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})

add_compile_options(-pipe -Wall -Wextra -Wpedantic)


## build macdylibbundler

set(BUNDLER_SRC ${CMAKE_SOURCE_DIR}/../resources/tools/macdylibbundler/src)

include_directories(BUNDLER_SRC)

add_executable(dylibbundler
    ${BUNDLER_SRC}/Dependency.cpp
    ${BUNDLER_SRC}/Dependency.h
    ${BUNDLER_SRC}/DylibBundler.cpp
    ${BUNDLER_SRC}/DylibBundler.h
    ${BUNDLER_SRC}/main.cpp
    ${BUNDLER_SRC}/Settings.cpp
    ${BUNDLER_SRC}/Settings.h
    ${BUNDLER_SRC}/Utils.cpp
    ${BUNDLER_SRC}/Utils.h
)

## build demo_app

set(DEMO_SRC ${CMAKE_SOURCE_DIR}/../demo_app)
set(PROJ_ICONS ${CMAKE_SOURCE_DIR}/../resources/icons)

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

# add_custom_target(Docs SOURCES README.md .gitignore LICENSE)

SET(app_resource_dir ${APP_NAME}.app/Contents/Resources)

# Destination paths below are relative to ${CMAKE_INSTALL_PREFIX}
install(TARGETS ${APP_NAME}
    BUNDLE DESTINATION . COMPONENT Runtime
    RUNTIME DESTINATION bin COMPONENT Runtime
    )

