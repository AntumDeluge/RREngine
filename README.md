
# RREngine

Rock &amp; Roll Engine

Plans for an engine to create Mega Man/Rockman style platform games.

---
### Licensing

Source: [MIT](LICENSE.txt)

Example data:

- sprite:
    - character (CC0): based on [Classic Hero by GrafxKid](https://opengameart.org/node/36173)

---
### Building

#### Required Libraries

- [SDL2](https://libsdl.org/)
- [SDL2_mixer](https://wiki.libsdl.org/SDL2_mixer)
- [SDL2_image](https://wiki.libsdl.org/SDL2_image)
- [TinyXML-2](http://leethomason.github.io/tinyxml2/)

#### Required Build Tools

- GNU compatible C++ compiler such as [gcc](https://www.gnu.org/software/gcc/) or [clang](https://clang.llvm.org/).
- [CMake](https://cmake.org/)

#### Running CMake Commands

1. Open a command line/terminal.
2. Change to the source root directory.

__Build in Source Root:__

3. Execute `cmake .` to generate build files.
4. Execute `cmake --build .` to build program.

__Build in Separate Directory:__

3. Execute `cmake -B <dir>` to generate build files in directory `<dir>`.
4. Execute `cmake --build <dir>` to build program in directory `<dir>`.

Example:

```bash
$ cmake -B build
-- Building for: Ninja
-- The C compiler identification is GNU 14.2.0
-- The CXX compiler identification is GNU 14.2.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: ... - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: ... - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found PkgConfig: ...
-- Checking for one of the modules 'SDL2_mixer>=2.0.0'
-- Checking for one of the modules 'SDL2_image>=2.0.0'
-- Checking for one of the modules 'tinyxml2'
-- Configuring done (2.9s)
-- Generating done (0.0s)
-- Build files have been written to: ...

$ cmake --build build
[1/9] Building CXX object ...
...
```

__Note:__ Build files can be regenerated with the `--fresh` option:

```bash
$ cmake --fresh -B build
```

If you generate build files from a directory other than the source root you must point to it:

```bash
$ mkdir build && cd build

$ cmake ../
...

$ cmake --build ../
...
```
