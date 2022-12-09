rm -rf ./build

pushd .

mkdir build
cd build
cmake ..
make

cpack -G ZIP

popd

