# Base template

This is a minimal base template to be used in another iterations.

see: <https://discourse.cmake.org/t/how-to-properly-use-bracket-arguments-in-install-code/6889/2>


> Just to flesh out your answer. Would it mean that I have something like a `fixup_osx.cmake.in` file which contains the `@var@` variables which are defined somewhere in the `CMakeLists.txt` file, and then use `configure_file` to take `fixup_osx.cmake.in` and output `fixup_osx.cmake` with the vars now expanded and then use `install(SCRIPT fixup_osx.cmake)` to execute the installation commands in that file.

