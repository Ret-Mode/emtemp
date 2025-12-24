emcmake cmake -B_ebuild -H. -DCMAKE_BUILD_TYPE=Release
#pushd _ebuild 
#emmake make
#popd
cmake --build _ebuild
