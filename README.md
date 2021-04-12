![Mikan banner](https://raw.githubusercontent.com/Riku32/mikan/master/assets/banner.png)

## Mikan
Mikan (ミカン) is a free, cross-platform, and open source Gameboy emulator project. It aims to be high performance, as close to standard as possible, and provide useful debugging tools for Gameboy developers and reverse engineers.

## Building
Building has been tested on Ubuntu and Windows.

### Build commands
```bash
git submodule update --init --recursive
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release --target app
```

### Resources
There was one primary resource used while developing the emulator, that was the [Gameboy Development Wiki](https://gbdev.gg8.se/wiki/articles/Main_Page). Each component of the emulator is accompanied with documentation and text from the wiki.