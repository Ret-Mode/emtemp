cmake -B_build -H.
cmake --build _build
cp ./_build/template ~/template
pushd ~
chmod +x ./template
./template
rm ./template
popd