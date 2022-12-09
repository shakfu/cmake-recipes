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

# Destination paths below are relative to ${CMAKE_INSTALL_PREFIX}
install(TARGETS ${APP_NAME}
    BUNDLE DESTINATION . COMPONENT Runtime
    RUNTIME DESTINATION bin COMPONENT Runtime
    )

# Note Mac specific extension .app
set(APPS "\${CMAKE_INSTALL_PREFIX}/${APP_NAME}.app")

# Directories to look for dependencies
set(DIRS ${CMAKE_BINARY_DIR})

install(CODE "include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")")

set(CPACK_GENERATOR "DRAGNDROP")
include(CPack)
