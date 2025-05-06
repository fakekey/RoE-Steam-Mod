mkdir build

cd build

cmake ^
    -GNinja ^
    -H"C:/Users/nghilq/Desktop/Chokevy" ^
    -DCMAKE_LIBRARY_OUTPUT_DIRECTORY="C:/Users/nghilq/Desktop/Chokevy/build" ^
    -DCMAKE_RUNTIME_OUTPUT_DIRECTORY="C:/Users/nghilq/Desktop/Chokevy/build" ^
    -B"C:/Users/nghilq/Desktop/Chokevy/build" ^
    ..

cmake --build .

cd ..