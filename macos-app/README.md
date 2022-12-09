# macos-app

This section was initially inspired by Ivan Onyshchenko's [cmake-bundle-macos](https://github.com/ionyshch/cmake-bundle-macos) as I was learning about cmake's osx bundling features.

Due to error in the initial configuration, I mistakenly thought that cmake only created the bundle but didn't yet have a feature of including dependent dylibs in the bundle. This lead me to another cool tool, Marianne Gagnon's [macdylibbundler](https://github.com/auriamg/macdylibbundler) which did this admirably.

Later, I realized my error and learned about the proper use `fixup_bundle` and `cpack` commands, and I was pleased to learn that dependency inclusion is built into cmake.

This project explores and experiments with different variations for OSX app bundling on cmake with or without the use of external tools (such as [macdylibbundler](https://github.com/auriamg/macdylibbundler))

## Building

The subprojects are in numbered folders. In each is a `CMakeLists.txt` and a `README.md`

To build all subprojects

```bash
make
```

To build a numbered subproject, just do `make <numbered-folder-name>`. For example:

```bash

make 01-osx-bundle

```

To clean after you are done experimenting:

```bash

make clean

```


## Todo

- [ ] more examples!

