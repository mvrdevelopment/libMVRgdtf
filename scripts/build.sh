# Make sure you run this script from the project's root dir.

rm -rf build
rm -rf output

mkdir build
cd build
cmake .. -DUNITTEST=TRUE -DEXTRA_LIBS="curl;icuuc;icudata;icui18n;icuio" -DXERCES_LIB_PATH="$(pwd)/../../xerces-c/_build/lib/libxerces-c.a"
make -j
cd ..

mkdir -p output/include
cp -r src/Include/* output/include/

mkdir -p output/lib
cp ../xerces-c/_build/lib/libxerces-c.a ./libs/libxerces-c.a
cp -r libs/* output/lib/