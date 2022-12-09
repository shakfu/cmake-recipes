# cmake cheatsheet


## bundling

```cmake
set_target_properties(<exe> PROPERTIES
 	INSTALL_RPATH_USE_LINK_PATH True
    MACOSX_BUNDLE_INFO_PLIST ${PROJECT_BINARY_DIR}/Info.plist
)
install(TARGETS <exe> BUNDLE DESTINATION <destdir>)
install(CODE "
        include(BundleUtilities)
        fixup_bundle(
        	\${CMAKE_INSTALL_PREFIX}/<destdir>/app.app
        	\"\" 
        	\"${DIRS}\")
        ")
```


## execute python script

```cmake
set(SCRIPTS_DIR "${PROJECT_SOURCE_DIR}/scripts")
execute_process(
	COMMAND ${PYTHON_EXECUTABLE} ${SCRIPTS_DIR}/script.py arg)
```

## properties on targets

### BINARY_DIR

This read-only property reports the value of the CMAKE_CURRENT_BINARY_DIR variable in the directory in which the target was defined.

### BUILD_RPATH

A semicolon-separated list specifying runtime path (RPATH) entries to add to binaries linked in the build tree (for platforms that support it). The entries will not be used for binaries in the install tree. See also the INSTALL_RPATH target property.

This property is initialized by the value of the variable CMAKE_BUILD_RPATH if it is set when a target is created.

This property supports generator expressions.


### BUILD_RPATH_USE_ORIGIN

Whether to use relative paths for the build RPATH.

This property is initialized by the value of the variable CMAKE_BUILD_RPATH_USE_ORIGIN.

On platforms that support runtime paths (RPATH) with the $ORIGIN token, setting this property to TRUE enables relative paths in the build RPATH for executables and shared libraries that point to shared libraries in the same build tree.

Normally the build RPATH of a binary contains absolute paths to the directory of each shared library it links to. The RPATH entries for directories contained within the build tree can be made relative to enable relocatable builds and to help achieve reproducible builds by omitting the build directory from the build environment.

This property has no effect on platforms that do not support the $ORIGIN token in RPATH, or when the CMAKE_SKIP_RPATH variable is set. The runtime path set through the BUILD_RPATH target property is also unaffected by this property.

### BUILD_WITH_INSTALL_NAME_DIR

A boolean specifying whether the macOS install_name of a target in the build tree uses the directory given by INSTALL_NAME_DIR. This setting only applies to targets on macOS.

This property is initialized by the value of the variable CMAKE_BUILD_WITH_INSTALL_NAME_DIR if it is set when a target is created.

If this property is not set and policy CMP0068 is not NEW, the value of BUILD_WITH_INSTALL_RPATH is used in its place.


### BUILD_WITH_INSTALL_RPATH

A boolean specifying whether to link the target in the build tree with the INSTALL_RPATH. This takes precedence over SKIP_BUILD_RPATH and avoids the need for relinking before installation.

This property is initialized by the value of the CMAKE_BUILD_WITH_INSTALL_RPATH variable if it is set when a target is created.

If policy CMP0068 is not NEW, this property also controls use of INSTALL_NAME_DIR in the build tree on macOS. Either way, the BUILD_WITH_INSTALL_NAME_DIR target property takes precedence.

### BUNDLE

This target is a CFBundle on the macOS.

If a module library target has this property set to true it will be built as a CFBundle when built on the mac. It will have the directory structure required for a CFBundle and will be suitable to be used for creating Browser Plugins or other application resources.

### BUNDLE_EXTENSION

The file extension used to name a BUNDLE, a FRAMEWORK, or a MACOSX_BUNDLE target on the macOS and iOS.

The default value is bundle, framework, or app for the respective target types.

### FRAMEWORK

Build SHARED or STATIC library as Framework Bundle on the macOS and iOS.

If such a library target has this property set to TRUE it will be built as a framework when built on the macOS and iOS. It will have the directory structure required for a framework and will be suitable to be used with the -framework option. This property is initialized by the value of the CMAKE_FRAMEWORK variable if it is set when a target is created.

To customize Info.plist file in the framework, use MACOSX_FRAMEWORK_INFO_PLIST target property.

For macOS see also the FRAMEWORK_VERSION target property.

Example of creation dynamicFramework:

```cmake
add_library(dynamicFramework SHARED
            dynamicFramework.c
            dynamicFramework.h
)
set_target_properties(dynamicFramework PROPERTIES
  FRAMEWORK TRUE
  FRAMEWORK_VERSION C
  MACOSX_FRAMEWORK_IDENTIFIER com.cmake.dynamicFramework
  MACOSX_FRAMEWORK_INFO_PLIST Info.plist
  # "current version" in semantic format in Mach-O binary file
  VERSION 16.4.0
  # "compatibility version" in semantic format in Mach-O binary file
  SOVERSION 1.0.0
  PUBLIC_HEADER dynamicFramework.h
  XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
)
```

### FRAMEWORK_VERSION

Version of a framework created using the FRAMEWORK target property (e.g. A).

This property only affects macOS, as iOS doesn't have versioned directory structure.



### INSTALL_NAME_DIR

Directory name for installed targets on Apple platforms.

INSTALL_NAME_DIR is a string specifying the directory portion of the "install_name" field of shared libraries on Apple platforms for installed targets. When not set, the default directory used is determined by MACOSX_RPATH. Policies CMP0068 and CMP0042 are also relevant.

This property is initialized by the value of the variable CMAKE_INSTALL_NAME_DIR if it is set when a target is created.

This property supports generator expressions. In particular, the `$<INSTALL_PREFIX` generator expression can be used to set the directory relative to the install-time prefix.


### INSTALL_REMOVE_ENVIRONMENT_RPATH

Controls whether toolchain-defined rpaths should be removed during installation.

When a target is being installed, CMake may need to rewrite its rpath information. This occurs when the install rpath (as specified by the INSTALL_RPATH target property) has different contents to the rpath that the target was built with. Some toolchains insert their own rpath contents into the binary as part of the build. By default, CMake will preserve those extra inserted contents in the install rpath. For those scenarios where such toolchain-inserted entries need to be discarded during install, set the INSTALL_REMOVE_ENVIRONMENT_RPATH target property to true.

This property is initialized by the value of CMAKE_INSTALL_REMOVE_ENVIRONMENT_RPATH when the target is created.


### INSTALL_RPATH

The rpath to use for installed targets.

A semicolon-separated list specifying the rpath to use in installed targets (for platforms that support it). This property is initialized by the value of the variable CMAKE_INSTALL_RPATH if it is set when a target is created.

Because the rpath may contain ${ORIGIN}, which coincides with CMake syntax, the contents of INSTALL_RPATH are properly escaped in the cmake_install.cmake script (see policy CMP0095.)

This property supports generator expressions.

### INSTALL_RPATH_USE_LINK_PATH

Add paths to linker search and installed rpath.

INSTALL_RPATH_USE_LINK_PATH is a boolean that if set to True will append to the runtime search path (rpath) of installed binaries any directories outside the project that are in the linker search path or contain linked library files. The directories are appended after the value of the INSTALL_RPATH target property.

This property is initialized by the value of the variable CMAKE_INSTALL_RPATH_USE_LINK_PATH if it is set when a target is created.


### LIBRARY_OUTPUT_DIRECTORY

Output directory in which to build LIBRARY target files.

This property specifies the directory into which library target files should be built. The property value may use generator expressions. Multi-configuration generators (Visual Studio, Xcode, Ninja Multi-Config) append a per-configuration subdirectory to the specified directory unless a generator expression is used.

This property is initialized by the value of the CMAKE_LIBRARY_OUTPUT_DIRECTORY variable if it is set when a target is created.

See also the `LIBRARY_OUTPUT_DIRECTORY_<CONFIG>` target property.


### Output name for LIBRARY target files.

This property specifies the base name for library target files. It overrides OUTPUT_NAME and `OUTPUT_NAME_<CONFIG>` properties.

See also the `LIBRARY_OUTPUT_NAME_<CONFIG>` target property.


### LINK_DEPENDS

Additional files on which a target binary depends for linking.

Specifies a semicolon-separated list of full-paths to files on which the link rule for this target depends. The target binary will be linked if any of the named files is newer than it.

This property is supported only by Ninja and Makefile Generators. It is intended to specify dependencies on "linker scripts" for custom Makefile link rules.

Contents of LINK_DEPENDS may use "generator expressions" with the syntax `$<...>`. See the cmake-generator-expressions(7) manual for available expressions. See the cmake-buildsystem(7) manual for more on defining buildsystem properties.

### LINK_DEPENDS_NO_SHARED

Do not depend on linked shared library files.

Set this property to true to tell CMake generators not to add file-level dependencies on the shared library files linked by this target. Modification to the shared libraries will not be sufficient to re-link this target. Logical target-level dependencies will not be affected so the linked shared libraries will still be brought up to date before this target is built.

This property is initialized by the value of the CMAKE_LINK_DEPENDS_NO_SHARED variable if it is set when a target is created.


### LINK_DIRECTORIES

List of directories to use for the link step of shared library, module and executable targets.

This property holds a semicolon-separated list of directories specified so far for its target. Use the target_link_directories() command to append more search directories.

This property is initialized by the LINK_DIRECTORIES directory property when a target is created, and is used by the generators to set the search directories for the linker.

Contents of LINK_DIRECTORIES may use "generator expressions" with the syntax $<...>. See the cmake-generator-expressions(7) manual for available expressions. See the cmake-buildsystem(7) manual for more on defining buildsystem properties.


### LINK_INTERFACE_LIBRARIES
### LINK_INTERFACE_MULTIPLICITY
### LINK_LIBRARIES
### LINK_LIBRARIES_ONLY_TARGETS
### LINK_LIBRARY_OVERRIDE
### LINK_OPTIONS

List of options to use for the link step of shared library, module and executable targets as well as the device link step. Targets that are static libraries need to use the STATIC_LIBRARY_OPTIONS target property.

These options are used for both normal linking and device linking (see policy CMP0105). To control link options for normal and device link steps, `$<HOST_LINK>` and `$<DEVICE_LINK>` generator expressions can be used.

This property holds a semicolon-separated list of options specified so far for its target. Use the target_link_options() command to append more options.

This property is initialized by the LINK_OPTIONS directory property when a target is created, and is used by the generators to set the options for the compiler.

Contents of LINK_OPTIONS may use "generator expressions" with the syntax $<...>. See the cmake-generator-expressions(7) manual for available expressions. See the cmake-buildsystem(7) manual for more on defining buildsystem properties.

Note This property must be used in preference to LINK_FLAGS property.
Host And Device Specific Link Options
New in version 3.18: When a device link step is involved, which is controlled by CUDA_SEPARABLE_COMPILATION and CUDA_RESOLVE_DEVICE_SYMBOLS properties and policy CMP0105, the raw options will be delivered to the host and device link steps (wrapped in -Xcompiler or equivalent for device link). Options wrapped with `$<DEVICE_LINK:...>` generator expression will be used only for the device link step. Options wrapped with `$<HOST_LINK:...>` generator expression will be used only for the host link step.

Option De-duplication

The final set of options used for a target is constructed by accumulating options from the current target and the usage requirements of its dependencies. The set of options is de-duplicated to avoid repetition.

New in version 3.12: While beneficial for individual options, the de-duplication step can break up option groups. For example, -option A -option B becomes -option A B. One may specify a group of options using shell-like quoting along with a SHELL: prefix. The SHELL: prefix is dropped, and the rest of the option string is parsed using the separate_arguments() UNIX_COMMAND mode. For example, "SHELL:-option A" "SHELL:-option B" becomes -option A -option B.

Handling Compiler Driver Differences

To pass options to the linker tool, each compiler driver has its own syntax. The LINKER: prefix and , separator can be used to specify, in a portable way, options to pass to the linker tool. LINKER: is replaced by the appropriate driver option and , by the appropriate driver separator. The driver prefix and driver separator are given by the values of the `CMAKE_<LANG>_LINKER_WRAPPER_FLAG` and `CMAKE_<LANG>_LINKER_WRAPPER_FLAG_SEP` variables.

For example, "LINKER:-z,defs" becomes -Xlinker -z -Xlinker defs for Clang and -Wl,-z,defs for GNU GCC.

The LINKER: prefix can be specified as part of a SHELL: prefix expression.

The LINKER: prefix supports, as an alternative syntax, specification of arguments using the SHELL: prefix and space as separator. The previous example then becomes "LINKER:SHELL:-z defs".

Note Specifying the SHELL: prefix anywhere other than at the beginning of the LINKER: prefix is not supported.

### LINK_LIBRARIES_ONLY_TARGETS

Enforce that link items that can be target names are actually existing targets.

Set this property to a true value to enable additional checks on the contents of the LINK_LIBRARIES and INTERFACE_LINK_LIBRARIES target properties, typically populated by target_link_libraries(). Checks are also applied to libraries added to a target through the INTERFACE_LINK_LIBRARIES_DIRECT properties of its dependencies. CMake will verify that link items that might be target names actually name existing targets. An item is considered a possible target name if:

- it does not contain a `/` or `\`, and

- it does not start in `-`, and

- (for historical reasons) it does not start in `$` or `.`

This property is initialized by the value of the CMAKE_LINK_LIBRARIES_ONLY_TARGETS variable when a non-imported target is created. The property may be explicitly enabled on an imported target to check its link interface.

In the following example, CMake will halt with an error at configure time because miLib is not a target:

```cmake
set(CMAKE_LINK_LIBRARIES_ONLY_TARGETS ON)
add_library(myLib STATIC myLib.c)
add_executable(myExe myExe.c)
target_link_libraries(myExe PRIVATE miLib) # typo for myLib
```
In order to link toolchain-provided libraries by name while still enforcing LINK_LIBRARIES_ONLY_TARGETS, use an imported Interface Library with the IMPORTED_LIBNAME target property:

```cmake
add_library(toolchain::m INTERFACE IMPORTED)
set_property(TARGET toolchain::m PROPERTY IMPORTED_LIBNAME "m")
target_link_libraries(myExe PRIVATE toolchain::m)
```

See also policy CMP0028.

Note If INTERFACE_LINK_LIBRARIES contains generator expressions, its actual list of link items may depend on the type and properties of the consuming target. In such cases CMake may not always detect names of missing targets that only appear for specific consumers. A future version of CMake with improved heuristics may start triggering errors on projects accepted by previous versions of CMake.


### MACOSX_BUNDLE

Build an executable as an Application Bundle on macOS or iOS.

When this property is set to TRUE the executable when built on macOS or iOS will be created as an application bundle. This makes it a GUI executable that can be launched from the Finder. See the MACOSX_BUNDLE_INFO_PLIST target property for information about creation of the Info.plist file for the application bundle. This property is initialized by the value of the variable CMAKE_MACOSX_BUNDLE if it is set when a target is created.

### MACOSX_BUNDLE_INFO_PLIST

Specify a custom `Info.plist` template for a macOS and iOS Application Bundle.

An executable target with MACOSX_BUNDLE enabled will be built as an application bundle on macOS. By default its `Info.plist` file is created by configuring a template called `MacOSXBundleInfo.plist.in` located in the CMAKE_MODULE_PATH. This property specifies an alternative template file name which may be a full path.

The following target properties may be set to specify content to be configured into the file:

`MACOSX_BUNDLE_BUNDLE_NAME`
Sets `CFBundleName`.

`MACOSX_BUNDLE_BUNDLE_VERSION`
Sets `CFBundleVersion`.

`MACOSX_BUNDLE_COPYRIGHT`
Sets `NSHumanReadableCopyright`.

`MACOSX_BUNDLE_GUI_IDENTIFIER`
Sets `CFBundleIdentifier`.

`MACOSX_BUNDLE_ICON_FILE`
Sets `CFBundleIconFile`.

`MACOSX_BUNDLE_INFO_STRING`
Sets `CFBundleGetInfoString`.

`MACOSX_BUNDLE_LONG_VERSION_STRING`
Sets `CFBundleLongVersionString`.

`MACOSX_BUNDLE_SHORT_VERSION_STRING`
Sets `CFBundleShortVersionString`.

CMake variables of the same name may be set to affect all targets in a directory that do not have each specific property set. If a custom Info.plist is specified by this property it may of course hard-code all the settings instead of using the target properties.



### MACOSX_FRAMEWORK_INFO_PLIST

Specify a custom Info.plist template for a macOS and iOS Framework.

A library target with FRAMEWORK enabled will be built as a framework on macOS. By default its Info.plist file is created by configuring a template called `MacOSXFrameworkInfo.plist.in` located in the CMAKE_MODULE_PATH. This property specifies an alternative template file name which may be a full path.

The following target properties may be set to specify content to be configured into the file:

`MACOSX_FRAMEWORK_BUNDLE_VERSION`
Sets `CFBundleVersion`.

`MACOSX_FRAMEWORK_ICON_FILE`
Sets `CFBundleIconFile`.

`MACOSX_FRAMEWORK_IDENTIFIER`
Sets `CFBundleIdentifier`.

`MACOSX_FRAMEWORK_SHORT_VERSION_STRING`
Sets `CFBundleShortVersionString`.

CMake variables of the same name may be set to affect all targets in a directory that do not have each specific property set. If a custom Info.plist is specified by this property it may of course hard-code all the settings instead of using the target properties.



### MACOSX_RPATH

Whether this target on macOS or iOS is located at runtime using rpaths.

When this property is set to TRUE, the directory portion of the install_name field of this shared library will be @rpath unless overridden by INSTALL_NAME_DIR. This indicates the shared library is to be found at runtime using runtime paths (rpaths).

This property is initialized by the value of the variable CMAKE_MACOSX_RPATH if it is set when a target is created.

Runtime paths will also be embedded in binaries using this target and can be controlled by the INSTALL_RPATH target property on the target linking to this target.

Policy CMP0042 was introduced to change the default value of MACOSX_RPATH to TRUE. This is because use of @rpath is a more flexible and powerful alternative to @executable_path and @loader_path.


### OSX_ARCHITECTURES

Target specific architectures for macOS.

The OSX_ARCHITECTURES property sets the target binary architecture for targets on macOS (-arch). This property is initialized by the value of the variable CMAKE_OSX_ARCHITECTURES if it is set when a target is created. Use `OSX_ARCHITECTURES_<CONFIG>` to set the binary architectures on a per-configuration basis, where `<CONFIG>` is an upper-case name (e.g. OSX_ARCHITECTURES_DEBUG).

```
OSX_ARCHITECTURES_<CONFIG>
XCODE_ATTRIBUTE_<an-attribute>
XCODE_EMBED_FRAMEWORKS_CODE_SIGN_ON_COPY
XCODE_EMBED_FRAMEWORKS_REMOVE_HEADERS_ON_COPY
XCODE_EMBED_<type>
XCODE_EMBED_<type>_CODE_SIGN_ON_COPY
XCODE_EMBED_<type>_PATH
XCODE_EMBED_<type>_REMOVE_HEADERS_ON_COPY
XCODE_EXPLICIT_FILE_TYPE
XCODE_GENERATE_SCHEME
XCODE_LINK_BUILD_PHASE_MODE
XCODE_PRODUCT_TYPE
XCODE_SCHEME_ADDRESS_SANITIZER
XCODE_SCHEME_ADDRESS_SANITIZER_USE_AFTER_RETURN
XCODE_SCHEME_ARGUMENTS
XCODE_SCHEME_DEBUG_AS_ROOT
XCODE_SCHEME_DEBUG_DOCUMENT_VERSIONING
XCODE_SCHEME_DISABLE_MAIN_THREAD_CHECKER
XCODE_SCHEME_DYNAMIC_LIBRARY_LOADS
XCODE_SCHEME_DYNAMIC_LINKER_API_USAGE
XCODE_SCHEME_ENABLE_GPU_API_VALIDATION
XCODE_SCHEME_ENABLE_GPU_FRAME_CAPTURE_MODE
XCODE_SCHEME_ENABLE_GPU_SHADER_VALIDATION
XCODE_SCHEME_ENVIRONMENT
XCODE_SCHEME_EXECUTABLE
XCODE_SCHEME_GUARD_MALLOC
XCODE_SCHEME_LAUNCH_CONFIGURATION
XCODE_SCHEME_LAUNCH_MODE
XCODE_SCHEME_MAIN_THREAD_CHECKER_STOP
XCODE_SCHEME_MALLOC_GUARD_EDGES
XCODE_SCHEME_MALLOC_SCRIBBLE
XCODE_SCHEME_MALLOC_STACK
XCODE_SCHEME_THREAD_SANITIZER
XCODE_SCHEME_THREAD_SANITIZER_STOP
XCODE_SCHEME_UNDEFINED_BEHAVIOUR_SANITIZER
XCODE_SCHEME_UNDEFINED_BEHAVIOUR_SANITIZER_STOP
XCODE_SCHEME_WORKING_DIRECTORY
XCODE_SCHEME_ZOMBIE_OBJECTS
XCODE_XCCONFIG
XCTEST
```
