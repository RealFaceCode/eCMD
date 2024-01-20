# Ecmd

A lightweight and simple C++ command interpreter. 🚀

## Table of Contents

- [Ecmd](#ecmd)
  - [Table of Contents](#table-of-contents)
  - [Download and build](#download-and-build)
    - [Download](#download)
    - [Build CMake](#build-cmake)
    - [Including in CMake project](#including-in-cmake-project)
    - [Build - Linux](#build---linux)
    - [Build - Windows](#build---windows)
  - [Example](#example)
  - [License](#license)

## Download and build

### Download

To get eCMD as a thirdparty dependencie use the folowing command:

```bash
git clone https://github.com/RealFaceCode/eCMD.git
```

### Build CMake

Building with cmake

```bash
mkdir build && cd build && cmake ..
```

### Including in CMake project

Including to your cmake projekt

```cmake
cmake_minimum_required(VERSION 3.5)
project(your_app VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS  "*.cpp")

add_subdirectory(eCMD)

add_executable(your_app ${SOURCE_FILES})
target_compile_features(your_app PRIVATE cxx_std_20)
target_include_directories(your_app PUBLIC thirdparty/eCMD/libBuild/hdr)
target_link_libraries(your_app PRIVATE eCMD)
```

### Build - Linux

Build with g++/gcc - unix

```bash
g++ -I./libBuild/hdr -shared -std=c++20 libBuild/src/*.cpp -o eCMD.so
```

### Build - Windows

Build with g++/gcc - windows

```bash
g++ -I./libBuild/hdr -shared -std=c++20 libBuild/src/*.cpp -o eCMD.dll
```

## Example

```cpp
#include <iostream>
#include "ecmd.hpp"

int main(int argc, const char** argv) 
{
    ecmd::CommandPrompt cmd(argc, argv, true);
    while(true)
    {
        if(!cmd.check())
            continue;

        while(cmd.argsLeft())
        {
            if(cmd.compare("test"))
                std::cout << "test" << std::endl;
            else if(cmd.compare("help"))
            {
                std::cout << "Available commands:" << std::endl;
                std::cout << "test" << std::endl;
                std::cout << "exit" << std::endl;
                std::cout << "help" << std::endl;
            }
            else if(cmd.compare("exit"))
                return 0;
            else
                std::cout << "Unknown command: " << cmd.lastCommand() << std::endl;
        }
    }

    return 0;
}
```

## License

Ecmd is open source and licensed under the [MIT License](LICENSE).

Made with ❤️ in C++.