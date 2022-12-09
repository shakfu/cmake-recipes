# Links and Notes


## Guides

- [Bundling c++ apps on macos using cmake](https://doc.magnum.graphics/magnum/platforms-macos.html)

- [Some notes about generating a macOS bundle with CMake](https://www.ferranpujolcamins.cat/2020/11/27/Notes-CMake-macOS-bundle.html
)

https://github.com/daid/EmptyEpsilon/wiki/Build%5CmacOS



## Bracket arguments don't work?

Some content on the internet provide examples of bracket arguments I can't seem to get working:

- [Can't use fixup_bundle() to create a portable bundle with Qt](https://stackoverflow.com/questions/17974439/cant-use-fixup-bundle-to-create-a-portable-bundle-with-qt)

- [CAN'T USE FIXUP_BUNDLE() TO CREATE A PORTABLE BUNDLE WITH QT](https://www.appsloveworld.com/cplus/100/114/cant-use-fixup-bundle-to-create-a-portable-bundle-with-qt)



```cmake
install(CODE [[
    include(BundleUtilities)
    fixup_bundle("${APPS}" "" "${DIRS}")
]] COMPONENT Runtime)
```
instead of 

```cmake
install(CODE "include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")")

```

The bracket argument form does not work.

It may have to do with seemingly required $ escaping here:

```cmake
set(APPS "\${CMAKE_INSTALL_PREFIX}/${APP_NAME}.app")
```

should try to:

```cmake
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
install(CODE "
    include(BundleUtilities)
    fixup_bundle(${CMAKE_INSTALL_PREFIX}/MyApp.app \"\" \"\")
" COMPONENT Runtime)
```


## cmake bundling examples

### build-python-with-cmake

Fascinating efforts to build python with cmake:

This on is quite active:

- [python-cmake-buildsystem](https://github.com/python-cmake-buildsystem/python-cmake-buildsystem)


This one is just starting:

- [gemini3d/cmake-python-build](https://github.com/gemini3d/cmake-python-build)


### single-function-as-script

From the [hiddenchest](https://github.com/edwinacunav/hiddenchest/blob/master/cmake/PrepUtils.cmake) project, a paramterized function.


```cmake
if(APPLE)
    function(PostBuildMacBundle target framework_list lib_list)
        INCLUDE(BundleUtilities)
        GET_TARGET_PROPERTY(_BIN_NAME ${target} LOCATION)
        GET_DOTAPP_DIR(${_BIN_NAME} _BUNDLE_DIR)

        set(_SCRIPT_FILE "${CMAKE_CURRENT_BINARY_DIR}/${target}_prep.cmake")
        file(WRITE ${_SCRIPT_FILE}
            "# Generated Script file\n"
            "include(BundleUtilities)\n"
            "get_bundle_and_executable(\"\${BUNDLE_APP}\" bundle executable valid)\n"
            "if(valid)\n"
            "  set(framework_dest \"\${bundle}/Contents/Frameworks\")\n"
            "  foreach(framework_path ${framework_list})\n"
            "    get_filename_component(framework_name \${framework_path} NAME_WE)\n"
            "    file(MAKE_DIRECTORY \"\${framework_dest}/\${framework_name}.framework/Versions/A/\")\n"
            "    copy_resolved_framework_into_bundle(\${framework_path}/Versions/A/\${framework_name} \${framework_dest}/\${framework_name}.framework/Versions/A/\${framework_name})\n"
            "  endforeach()\n"
            "  foreach(lib ${lib_list})\n"
            "    get_filename_component(lib_file \${lib} NAME)\n"
            "    copy_resolved_item_into_bundle(\${lib} \${framework_dest}/\${lib_file})\n"
            "  endforeach()\n"
            "else()\n"
            "  message(ERROR \"App Not found? \${BUNDLE_APP}\")\n"
            "endif()\n"
            "#fixup_bundle(\"\${BUNDLE_APP}\" \"\" \"\${DEP_LIB_DIR}\")\n"
        )

        ADD_CUSTOM_COMMAND(TARGET ${target}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -DBUNDLE_APP="${_BUNDLE_DIR}" -P "${_SCRIPT_FILE}"
        )
    endfunction()
else()
    function(PostBuildMacBundle target framework_list lib_list)
        # noop
    endfunction()
endif()
```

shouldn't this be made more readable as:

```cmake
if(APPLE)
    function(PostBuildMacBundle target framework_list lib_list)
        INCLUDE(BundleUtilities)
        GET_TARGET_PROPERTY(_BIN_NAME ${target} LOCATION)
        GET_DOTAPP_DIR(${_BIN_NAME} _BUNDLE_DIR)

        set(_SCRIPT_FILE "${CMAKE_CURRENT_BINARY_DIR}/${target}_prep.cmake")
        file(WRITE ${_SCRIPT_FILE} [[
            # Generated Script file
            include(BundleUtilities)
            get_bundle_and_executable("${BUNDLE_APP}" bundle executable valid)
            if(valid)
                set(framework_dest "${bundle}/Contents/Frameworks")
                foreach(framework_path ${framework_list})
                    get_filename_component(framework_name ${framework_path} NAME_WE)
                    file(MAKE_DIRECTORY "${framework_dest}/${framework_name}.framework/Versions/A/")
                    copy_resolved_framework_into_bundle(
                        ${framework_path}/Versions/A/${framework_name}
                        ${framework_dest}/${framework_name}.framework/Versions/A/${framework_name}
                    )
                endforeach()
                foreach(lib ${lib_list})
                    get_filename_component(lib_file ${lib} NAME)
                    copy_resolved_item_into_bundle(${lib} ${framework_dest}/${lib_file})
                endforeach()
            else()
                message(ERROR "App Not found? ${BUNDLE_APP}")
            endif()
            "#fixup_bundle("${BUNDLE_APP}" "" "${DEP_LIB_DIR}")
            ]]
        )

        ADD_CUSTOM_COMMAND(TARGET ${target}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -DBUNDLE_APP="${_BUNDLE_DIR}" -P "${_SCRIPT_FILE}"
        )
    endfunction()
else()
    function(PostBuildMacBundle target framework_list lib_list)
        # noop
    endfunction()
endif()
```

## Another fixup function


https://github.com/NGSolve/ngsolve/blob/master/cmake/package_osx_fixup.cmake.in

```cmake
# override default behaviour to embed .dylib files to Macos instead of Frameworks
function(gp_item_default_embedded_path_override item default_embedded_path_var)
  set(path "@executable_path")
  if(APPLE)
    set(path "@loader_path/../../Contents/MacOS")

    # Embed only frameworks (and NOT .dylibs) in the embedded "Frameworks" directory
    if(item MATCHES "[^/]+\\.framework/")
      set(path "@executable_path/../Frameworks")
    endif()
  endif()
  set(${default_embedded_path_var} "${path}" PARENT_SCOPE)
endfunction()

include(BundleUtilities)

function(fixup_bundle1 app libs dirs)
  message(STATUS "fixup_bundle")
  message(STATUS "  app='${app}'")
  message(STATUS "  libs='${libs}'")
  message(STATUS "  dirs='${dirs}'")

  set(options)
  set(oneValueArgs)
  set(multiValueArgs IGNORE_ITEM)
  cmake_parse_arguments(CFG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

  message(STATUS "  ignoreItems='${CFG_IGNORE_ITEM}'")

  get_bundle_and_executable("${app}" bundle executable valid)
  if(valid)
    get_filename_component(exepath "${executable}" PATH)

    message(STATUS "fixup_bundle: preparing...")
    get_bundle_keys("${app}" "${libs}" "${dirs}" keys IGNORE_ITEM "${CFG_IGNORE_ITEM}")

    list(REMOVE_ITEM keys "Python" ) # skip fixup of Python
    foreach(key "Python") # skip fixup of Python${keys})
        message("unset ${key}_COPYFLAG")
        unset(${key}_COPYFLAG)
        unset(${key}_DEFAULT_EMBEDDED_PATH)
        unset(${key}_EMBEDDED_ITEM)
        unset(${key}_ITEM)
        unset(${key}_RDEP_RPATHS)
        unset(${key}_RESOLVED_EMBEDDED_ITEM)
        unset(${key}_RESOLVED_ITEM)
        unset(${key}_RPATHS)
    endforeach()

    message(STATUS "fixup_bundle: copying...")
    list(LENGTH keys n)
    math(EXPR n ${n}*2)

    set(i 0)
    foreach(key ${keys})
      math(EXPR i ${i}+1)
      if("${${key}_COPYFLAG}" STREQUAL "2")
        message(STATUS "${i}/${n}: linking '${${key}_RESOLVED_ITEM}' -> '${${key}_RESOLVED_EMBEDDED_ITEM}'")
      elseif(${${key}_COPYFLAG})
        message(STATUS "${i}/${n}: copying '${${key}_RESOLVED_ITEM}'")
      else()
        message(STATUS "${i}/${n}: *NOT* copying '${${key}_RESOLVED_ITEM}'")
      endif()

      set(show_status 1)
      if(show_status)
        message(STATUS "key='${key}'")
        message(STATUS "item='${${key}_ITEM}'")
        message(STATUS "resolved_item='${${key}_RESOLVED_ITEM}'")
        message(STATUS "default_embedded_path='${${key}_DEFAULT_EMBEDDED_PATH}'")
        message(STATUS "embedded_item='${${key}_EMBEDDED_ITEM}'")
        message(STATUS "resolved_embedded_item='${${key}_RESOLVED_EMBEDDED_ITEM}'")
        message(STATUS "copyflag='${${key}_COPYFLAG}'")
        message(STATUS "")
      endif()

      if("${${key}_COPYFLAG}" STREQUAL "2")
        link_resolved_item_into_bundle("${${key}_RESOLVED_ITEM}"
          "${${key}_RESOLVED_EMBEDDED_ITEM}")
      elseif(${${key}_COPYFLAG})
        set(item "${${key}_ITEM}")
        if(item MATCHES "[^/]+\\.framework/")
          copy_resolved_framework_into_bundle("${${key}_RESOLVED_ITEM}"
            "${${key}_RESOLVED_EMBEDDED_ITEM}")
        else()
          copy_resolved_item_into_bundle("${${key}_RESOLVED_ITEM}"
            "${${key}_RESOLVED_EMBEDDED_ITEM}")
        endif()
      endif()
    endforeach()

    message(STATUS "fixup_bundle: fixing...")
    foreach(key ${keys})
      math(EXPR i ${i}+1)
      if(APPLE)
        message(STATUS "${i}/${n}: fixing up '${${key}_RESOLVED_EMBEDDED_ITEM}'")
        if(NOT "${${key}_COPYFLAG}" STREQUAL "2")
          fixup_bundle_item("${${key}_RESOLVED_EMBEDDED_ITEM}" "${exepath}" "${dirs}")
        endif()
      else()
        message(STATUS "${i}/${n}: fix-up not required on this platform '${${key}_RESOLVED_EMBEDDED_ITEM}'")
      endif()
    endforeach()

    message(STATUS "fixup_bundle: cleaning up...")
    clear_bundle_keys(keys)

    message(STATUS "fixup_bundle: verifying...")
    # verify_app("${app}" IGNORE_ITEM "${CFG_IGNORE_ITEM}")
  else()
    message(SEND_ERROR "error: fixup_bundle: not a valid bundle")
  endif()

  message(STATUS "fixup_bundle: done")
endfunction()

get_filename_component(APPNAME @CMAKE_INSTALL_PREFIX@ NAME)
set(APP "${CMAKE_CURRENT_BINARY_DIR}/bundle_dir/${APPNAME}")
set(MACOS_DIR ${APP}/Contents/MacOS)

set(BU_CHMOD_BUNDLE_ITEMS ON)

message("copy @CMAKE_INSTALL_PREFIX@ dir to bundle_dir")
execute_process(COMMAND mkdir bundle_dir)
execute_process(COMMAND cp -r @CMAKE_INSTALL_PREFIX@ bundle_dir)
execute_process(COMMAND ln -s /Applications bundle_dir/Applications)

file(GLOB libs ${MACOS_DIR}/*.dylib ${MACOS_DIR}/*.so)
message("libraries to fix: ${libs}")
fixup_bundle1( ${MACOS_DIR}/netgen "${libs}" "${MACOS_DIR}") # IGNORE_ITEM ${libs})
message("create image")
execute_process(COMMAND hdiutil create -size 200m -volname NGSolve -srcfolder bundle_dir -ov -fs HFS+ -format UDZO NGSolve-@NGSOLVE_VERSION@.dmg)
execute_process(COMMAND otool -L ${MACOS_DIR}/netgen)
message("delete bundle_dir")
execute_process(COMMAND rm -rf bundle_dir)
```




## Other examples


https://github.com/KiCad/kicad-source-mirror/blob/490069c5e66ad8c23a031e5856db2d5c23c2f841/eeschema/CMakeLists.txt

https://github.com/KhronosGroup/Vulkan-Tools/blob/c4839afe758d3c8fb5c46792398509b4fee0a28a/cube/CMakeLists.txt

https://github.com/KhronosGroup/Vulkan-Tools/blob/c4839afe758d3c8fb5c46792398509b4fee0a28a/vulkaninfo/macOS/vulkaninfo.cmake

https://github.com/HarbourMasters/Shipwright/blob/20cbebeed76a33ab8a202988243026f0c8d53469/CMakeLists.txt

https://github.com/tylerastraub/StraubEngine/blob/9673909f5e507f15f03c0d55ff7bf742da492665/CMakeLists.txt

https://github.com/SteeKsi/AudioDSP/blob/f7c1b4a3a2797aa9e56734e36b8ea492b394332d/Libraries/marsyas/src/qt5apps/inspector/CMakeLists.txt

https://github.com/ahnan4arch/plex-home-theatre-extra/blob/b15cc1901c1889e6bbae872e35b77126c522f78c/plex/CMakeCompleteBundle.cmake.in


https://github.com/elfmz/far2l/blob/6a5e9b6e53a072843292554b14c57918a9687ab1/packaging/osx/FixupBundle.cmake


https://github.com/lsroe/ngsolve/blob/63c0dcb624f05e8dfa7097b03a2e76496a546887/cmake/package_osx_fixup.cmake.in

https://github.com/webosose/chromium87/blob/83784a81f0a9689518b45451205bdb594bd1cbab/src/third_party/angle/third_party/vulkan-tools/src/cube/CMakeLists.txt


## tests

https://github.com/Universite-Gustave-Eiffel/I-Simpa/blob/a0d4d4330d8c9894d31ce80e0fd3a9a1d4b872cb/src/python_bindings/CMakeLists.txt




## Python

- [Building python extensions with cmake](https://martinopilia.com/posts/2018/09/15/building-python-extension.html)


https://github.com/aashish24/paraview-climate-3.11.1/blob/c8ea429f56c10059dfa4450238b8f5bac3208d3a/VTK/Utilities/Release/CMakeLists.txt


https://github.com/GoAnimate-Stuff-by-Zoccorus/wrapper-offline/blob/b395bc6e4e8809019012f4f417411a930cea4085/utilities/sourcecode/avidemux2-master/avidemux/osxInstaller/cmake/admFixupBundle.cmake.in


https://github.com/friskyweasel/OpenPHT/blob/f4031639a1dd0a8285d9b8048c7e7f2528bdcd44/plex/CMakeCompleteBundle.cmake.in

https://github.com/mean00/avidemux2/blob/f60b6195b0597eded19fb3c49013ef819cc9be6c/avidemux/osxInstaller/cmake/admFixupBundle.cmake.in


## Issue

https://gitlab.kitware.com/cmake/cmake/-/issues/16625

https://cmake.org/pipermail/cmake/2010-November/040898.html

