# Route_Planning_Project
Welcome to the first project of C++ Nanodegree! In this project, I will create a route planner that plots a path between two points on a map using real map data from the [OpenStreeMap project](https://www.openstreetmap.org/#map=5/-28.153/133.275).

## Environment
👉 macOS 11.5.2 Big Sur with Intel Core i7 chip
👉 Homebrew 3.2.10
👉 cMake 3.21.2
👉 GNU Make 3.81
👉 C++ 17
👉 Apple clang version 12.0.5
👉 IO2D

## Installing IO2D
This library must be built inside the [thirdparty](thirdparty) folder so CMake `find_package` can find it.

The steps found [here](https://github.com/cpp-io2d/P0267_RefImpl/blob/master/BUILDING.md) for [Cairo/Mac](https://github.com/cpp-io2d/P0267_RefImpl/blob/master/BUILDING.md#cairoxlib-on-macos) or [CoreGraphics/Mac](https://github.com/cpp-io2d/P0267_RefImpl/blob/master/BUILDING.md#coregraphicsmac-on-macos) didn't work for me. I had to tweak a few things to install the library and get the whole project to build.

If you are having issues installing IO2D in macOS Big Sur, follow these steps and let me know if it worked for you too!

1. Download [libc++](http://releases.llvm.org/6.0.0/clang+llvm-6.0.0-x86_64-apple-darwin.tar.xz) and extract its contents in [thirdparty](thirdparty) folder. For easy use, rename the folder to `clang`
2. Setup `CXXFLAGS` and `LDFLAGS` as follows (**replace YOURUSER with your username**)
```
export CXXFLAGS="-nostdinc++ -isystem/Users/YOURUSER/GitHub/Route_Planning_Project/thirdparty/clang/include/c++/v1"
export LDFLAGS="-L/Users/YOURUSER/GitHub/Route_Planning_Project/thirdparty/clang/lib -Wl,-rpath,/Users/YOURUSER/GitHub/Route_Planning_Project/thirdparty/clang/lib"
```
3. Install libpng `brew install libpng`
4. Install graphicsmagick `brew install graphicsmagick`
5. Install [MacPorts](https://www.macports.org/install.php)
6. Install Cairo using MacPorts `Install Cairo: sudo /opt/local/bin/port -N -k install cairo +x11`
7. Exports `CXXFLAGS` and `LDFLAGS` to include new paths
```
export CXXFLAGS="$CXXFLAGS -isystem/opt/X11/include -isystem/opt/local/include -isystem/usr/local/include"
export LDFLAGS="$LDFLAGS -L/opt/X11/lib -L/opt/local/lib -L/usr/local/lib"
```
8. Enter thirdparty folder and commit the IO2D repo as follows
```
cd thirdparty
git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl
cd P0267_RefImpl
```
9. Before building, you will need to modify the `CMakeLists.txt` file by commenting out the samples part. Just look for:
```
if( NOT DEFINED IO2D_WITHOUT_SAMPLES )
 add_subdirectory(P0267_RefImpl/Samples)
endif()
```
and replace with
```
#[[
if( NOT DEFINED IO2D_WITHOUT_SAMPLES )
 add_subdirectory(P0267_RefImpl/Samples)
endif()
]]
```
10. Save the file and now create the Debug folder `mkdir Debug && cd Debug`
11. Run the CMake command `cmake -G "Xcode" -S Debug "-DCMAKE_BUILD_TYPE=Debug" ../.`
12. Open the project in Xcode with `open io2d.xcodeproj` and run `ALL_BUILD` and `install` schemes (Product>Scheme>all_build and press the play button and Product>Schema>install and press play button)
13. Navigate to the project root directory again and make a build folder and enter it
```
cd /Users/YOURUSER/GitHub/Route_Planning_Project/
mkdir build && cd build
```
14. Before running the cmake and make commands, modify the root `CMakeLists.txt` by adding after the `cmake_minimum_required` line:
```
set(CMAKE_EXE_LINKER_FLAGS "-L/usr/local/opt/llvm/lib -Wl,-rpath,/usr/local/opt/llvm/lib -L/opt/X11/lib -L/opt/local/lib -L/usr/local/lib")
set(ENV{CPPFLAGS} "-I/usr/local/opt/llvm/include -I/opt/X11/include")
set(CMAKE_CXX_FLAGS "-nostdinc++ -isystem/usr/local/opt/llvm/include/c++/v1 -isystem/opt/X11/include -isystem/opt/local/include -isystem/usr/local/include")
```
Also add `add_subdirectory(thirdparty/P0267_RefImpl)` after the `add_subdirectory(thirdparty/googletest)`
15. Run `cmake ..` and `make`
16. Finally run `./OSM_A_star_search` and it should show the map in a new X11 window

## Compiling and Running
### Compile
Before compiling this repository, please modify `variables.zsh` with your project absolute path and then source it. This file exports the `CXXFLAGS` and `LDFLAGS`.

Then, create a `build` folder and change to that directory
```
mkdir build && cd build
```

Within the build directory run
```
cmake ..
make
```

### Running
The executable is within the `build` directory. You can run it as follows
```
./OSM_A_star_search
```

## Testing
Udacity has provided a series of GoogleTests and you can run them within the build directory as follows
```
./test
```
