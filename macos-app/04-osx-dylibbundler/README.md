# About this variation

# Building

You can build the long way or the short way (both do the same thing):

- The long way:

```bash
mkdir build
cd build
cmake ..
./dylibbundler -od -b\
  -s . \
  -x ./PortableApp.app/Contents/MacOS/PortableApp \
  -d ./PortableApp.app/Contents/Frameworks \
  -p @executable_path/../Frameworks
cpack -G DragNDrop
```

- The short way: `./build.sh`


## Todo


## Credits / License

### Portable sample app for cmake and cpack

You are welcome to contact me at **ivan.onyshchenko (at) gmail.com** in case you have any questions, comments, suggestions or need help building, designing or implementing your product.

### macdylibbundler

The MIT License (MIT)

Copyright (c) 2014 Marianne Gagnon

