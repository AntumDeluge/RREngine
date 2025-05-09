
# Building Source Code

See [downloads section](download.md) for how to get source code.

## Required Libraries

### Bundled Libraries

- [cxxopts](https://github.com/jarro2783/cxxopts) v3.2.0 ([MIT](lib/cxxopts/LICENSE.txt))
- [lua](https://lua.org/) v5.4.7 ([MIT](lib/lua/LICENSE.txt)) _(disabled)_
- [tmxlite](https://github.com/fallahn/tmxlite) v1.4.4 (zlib)

### External Libraries

- [SDL2](https://libsdl.org/) (zlib) ([source](https://github.com/libsdl-org/SDL/releases))
- [SDL2_mixer](https://wiki.libsdl.org/SDL2_mixer) (zlib) ([source](https://github.com/libsdl-org/SDL_mixer/releases))
- [SDL2_image](https://wiki.libsdl.org/SDL2_image) (zlib) ([source](https://github.com/libsdl-org/SDL_image/releases))
- [pugixml](https://pugixml.org/) (MIT) ([source](https://github.com/zeux/pugixml))

## Required Build Tools

- GNU compatible C++ compiler such as [gcc](https://www.gnu.org/software/gcc/) or
  [clang](https://clang.llvm.org/) with C++20 support (untested with other compilers).
- [CMake](https://cmake.org/)
- [pkg-config](https://www.freedesktop.org/wiki/Software/pkg-config/) or [pkgconf](http://pkgconf.org/)

## Running CMake Commands

1. Open a command line/terminal.
2. Change to the source root directory.

### Build in Source Root

3. Execute `cmake .` to generate build files.
4. Execute `cmake --build .` to build program executable.

### Build in Separate Directory

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
