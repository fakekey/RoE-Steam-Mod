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

move Chokevy.dll "C:/Users/nghilq/Desktop/Fakekey2k"

cd ..