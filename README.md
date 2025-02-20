# RREngine
Rock &amp; Roll Engine

Plans for an engine to create Mega Man/Rockman style platform games.

---
### Building

#### Required Libraries

- [SDL](https://libsdl.org/)

#### Required Build Tools

- GNU compatible C++ compiler such as [gcc](https://www.gnu.org/software/gcc/) or [clang](https://clang.llvm.org/).
- [CMake](https://cmake.org/)

#### Running CMake Commands

The CMake cache/build files are created in the current working directory. You can simply
run `cmake ./` from the source root directory. To create files in a different directory,
specify where source root is located:

```bash
$ mkdir build
$ cd build
$ cmake ../
```

Then you can execute the build process using the following commands:

```bash
$ make

# alternatively use CMake's build command
$ cmake --build ./
```
