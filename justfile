build:
    cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="$DEVKITPRO/cmake/GBA.cmake"
    cmake --build build

clean:
    cmake --build build --target clean

run: (build)
    open ./build/gbafire.gba
