![Mikan banner](https://raw.githubusercontent.com/Riku32/mikan/master/assets/banner.png)

## Mikan
Mikan (ミカン) is a free and open source high performance Gameboy emulator project. It aims to be high performance, as close to standard as possible, and provide useful debugging tools for Gameboy developers and reverse engineers.

## Building
Building has been tested on Ubuntu and Windows. On Windows all dependencies are taken care of, on Linux please make sure you have sdl2 development libraries installed.

### Build commands
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release --target app
```
**IMPORTANT: For building on windows make sure to add `-A win32` at the end of the second command in the build commands above**