mkdir build

cd build

cmake ^
    -GNinja ^
    -H"C:/Users/fakekey2k/Desktop/Chokevy" ^
    -DCMAKE_LIBRARY_OUTPUT_DIRECTORY="C:/Users/fakekey2k/Desktop/Chokevy/build" ^
    -DCMAKE_RUNTIME_OUTPUT_DIRECTORY="C:/Users/fakekey2k/Desktop/Chokevy/build" ^
    -B"C:/Users/fakekey2k/Desktop/Chokevy/build" ^
    ..

cmake --build .

cd ..