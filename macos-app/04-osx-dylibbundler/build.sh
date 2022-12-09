rm -rf ./build

pushd .

mkdir build
cd build
cmake ..
make
echo `pwd`
./dylibbundler -od -b \
  -s . \
  -x ./DemoApp.app/Contents/MacOS/DemoApp \
  -d ./DemoApp.app/Contents/Frameworks \
  -p @executable_path/../Frameworks

popd

