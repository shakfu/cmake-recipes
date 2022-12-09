rm -rf ./build

pushd .

mkdir build
cd build
cmake ..
make

popd

