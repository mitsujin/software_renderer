# SoftRenderer

A C++ software renderer project using SDL2 for graphics and window management.

## Features

- SDL2 integration for cross-platform graphics
- CMake build system
- Modern C++17 standard
- Basic window and rendering setup

## Prerequisites

### Ubuntu/Debian
```bash
sudo apt update
sudo apt install build-essential cmake libsdl2-dev
```

### Fedora/RHEL
```bash
sudo dnf install gcc-c++ cmake SDL2-devel
```

### macOS
```bash
brew install cmake sdl2
```

### Windows
- Install Visual Studio with C++ support
- Install SDL2 development libraries
- Or use vcpkg: `vcpkg install sdl2`

## Building

1. Create a build directory:
```bash
mkdir build
cd build
```

2. Configure with CMake:
```bash
cmake ..
```

3. Build the project:
```bash
make
```

4. Run the application:
```bash
./softrenderer
```

## Project Structure

```
softrenderer/
├── CMakeLists.txt      # Main build configuration
├── src/
│   └── main.cpp        # Main application entry point
├── README.md           # This file
└── LICENSE             # Project license
```

## What it does

The current implementation creates a window with a white rectangle on a black background. This serves as a foundation for building a software renderer.

## Next Steps

- Implement basic rasterization
- Add triangle rendering
- Implement depth buffer
- Add texture mapping
- Implement lighting and shading

## License

See LICENSE file for details.
