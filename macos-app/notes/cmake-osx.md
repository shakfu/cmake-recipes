# Cmake Cheatsheet for MACOSX

## Cmake Variables


## Cmake Properties

### Properties on Source

#### MACOSX_PACKAGE_LOCATION

see: [MACOSX_PACKAGE_LOCATION](https://cmake.org/cmake/help/latest/prop_sf/MACOSX_PACKAGE_LOCATION.html)

Place a source file inside a Application Bundle (MACOSX_BUNDLE), Core Foundation Bundle (BUNDLE), or Framework Bundle (FRAMEWORK). It is applicable for macOS and iOS.

- Executable targets with the MACOSX_BUNDLE property set are built as macOS or iOS application bundles on Apple platforms.

- Shared library targets with the FRAMEWORK property set are built as macOS or iOS frameworks on Apple platforms.

- Module library targets with the BUNDLE property set are built as macOS CFBundle bundles on Apple platforms.

Source files listed in the target with this property set will be **copied to a directory inside the bundle or framework content folder specified by the property value**.

For macOS Application Bundles the content folder is `<name>.app/Contents`. 

For macOS Frameworks the content folder is `<name>.framework/Versions/<version>`.

For macOS CFBundles the content folder is `<name>.bundle/Contents` (unless the extension is changed).

See the PUBLIC_HEADER, PRIVATE_HEADER, and RESOURCE target properties for specifying files meant for `Headers`, `PrivateHeaders`, or `Resources` directories.

If the specified location is equal to `Resources`, the resulting location will be the same as if the RESOURCE property had been used. If the specified location is a sub-folder of `Resources`, it will be placed into the respective sub-folder.

Note: For iOS Apple uses a flat bundle layout where no `Resources` folder exist. Therefore CMake strips the Resources folder name from the specified location.


### Properties on Targets

#### MACOSX_BUNDLE

Build an executable as an Application Bundle on macOS or iOS.

When this property is set to TRUE the executable when built on macOS or iOS will be created as an application bundle. This makes it a GUI executable that can be launched from the Finder. See the MACOSX_BUNDLE_INFO_PLIST target property for information about creation of the `Info.plist` file for the application bundle. This property is initialized by the value of the variable CMAKE_MACOSX_BUNDLE if it is set when a target is created.


#### MACOSX_BUNDLE_INFO_PLIST

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


#### MACOSX_FRAMEWORK_INFO_PLIST

Specify a custom Info.plist template for a macOS and iOS Framework.

A library target with FRAMEWORK enabled will be built as a framework on macOS. By default its `Info.plist` file is created by configuring a template called `MacOSXFrameworkInfo.plist.in` located in the CMAKE_MODULE_PATH. This property specifies an alternative template file name which may be a full path.

The following target properties may be set to specify content to be configured into the file:

`MACOSX_FRAMEWORK_BUNDLE_VERSION`
	Sets `CFBundleVersion`.

`MACOSX_FRAMEWORK_ICON_FILE`
	Sets `CFBundleIconFile`.

`MACOSX_FRAMEWORK_IDENTIFIER`
	Sets `CFBundleIdentifier`.

`MACOSX_FRAMEWORK_SHORT_VERSION_STRING`
	Sets `CFBundleShortVersionString`.

CMake variables of the same name may be set to affect all targets in a directory that do not have each specific property set. If a custom `Info.plist` is specified by this property it may of course hard-code all the settings instead of using the target properties.


#### MACOSX_RPATH

Whether this target on macOS or iOS is located at runtime using rpaths.

When this property is set to TRUE, the directory portion of the `install_name` field of this shared library will be `@rpath` unless overridden by INSTALL_NAME_DIR. This indicates the shared library is to be found at runtime using runtime paths (rpaths).

This property is initialized by the value of the variable CMAKE_MACOSX_RPATH if it is set when a target is created.

Runtime paths will also be embedded in binaries using this target and can be controlled by the INSTALL_RPATH target property on the target linking to this target.

Policy CMP0042 was introduced to change the default value of MACOSX_RPATH to TRUE. This is because use of `@rpath` is a more flexible and powerful alternative to `@executable_path` and `@loader_path`.


#### RESOURCE


Specify resource files in a FRAMEWORK or BUNDLE.

Target marked with the FRAMEWORK or BUNDLE property generate framework or application bundle (both macOS and iOS is supported) or normal shared libraries on other platforms. This property may be set to a list of files to be placed in the corresponding directory (eg. `Resources` directory for macOS) inside the bundle. On non-Apple platforms these files may be installed using the RESOURCE option to the install(TARGETS) command.

Following example of Application Bundle:

```cmake
add_executable(ExecutableTarget
  addDemo.c
  resourcefile.txt
  appresourcedir/appres.txt)

target_link_libraries(ExecutableTarget heymath mul)

set(RESOURCE_FILES
  resourcefile.txt
  appresourcedir/appres.txt)

set_target_properties(ExecutableTarget PROPERTIES
  MACOSX_BUNDLE TRUE
  MACOSX_FRAMEWORK_IDENTIFIER org.cmake.ExecutableTarget
  RESOURCE "${RESOURCE_FILES}")
```
will produce flat structure for iOS systems:

```text
ExecutableTarget.app
  appres.txt
  ExecutableTarget
  Info.plist
  resourcefile.txt
```

For macOS systems it will produce following directory structure:

```
ExecutableTarget.app/
  Contents
    Info.plist
    MacOS
      ExecutableTarget
    Resources
      appres.txt
      resourcefile.txt
```

For Linux, such CMake script produce following files:

```
ExecutableTarget
Resources
  appres.txt
  resourcefile.txt
```

#### PUBLIC_HEADER

Specify public header files in a FRAMEWORK shared library target.

Shared library targets marked with the FRAMEWORK property generate frameworks on macOS, iOS and normal shared libraries on other platforms. This property may be set to a list of header files to be placed in the Headers directory inside the framework folder. On non-Apple platforms these headers may be installed using the PUBLIC_HEADER option to the install(TARGETS) command.

#### PRIVATE_HEADER

Specify private header files in a FRAMEWORK shared library target.

Shared library targets marked with the FRAMEWORK property generate frameworks on macOS, iOS and normal shared libraries on other platforms. This property may be set to a list of header files to be placed in the PrivateHeaders directory inside the framework folder. On non-Apple platforms these headers may be installed using the PRIVATE_HEADER option to the install(TARGETS) command.


## Cmake Commands

- [install](https://cmake.org/cmake/help/latest/command/install.html#command:install)

