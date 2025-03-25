
# R&R Engine (Rock & Roll Engine)

---
## Description

_(this software is a work-in-progress & not yet fully functional)_

An engine to create [Mega Man/Rockman](https://en.wikipedia.org/wiki/Mega_Man) style platform games.

---
## Licensing

Source: [MIT](LICENSE.txt)

Example data:

- sprite:
    - character (CC0): based on [Classic Hero by GrafxKid](https://opengameart.org/node/36173)
    - enemy (CC0): [Classic Hero and Baddies Pack by GrafxKid](https://opengameart.org/node/36173)
- tileset:
    - grassland (CC0): [Grassy Tileset by ImpossibleRealms](https://opengameart.org/node/66391)
- backgrounds:
    - [underwater_mountains](https://opengameart.org/node/28985) by
      [PumpkinGlitters](https://pumpkingitters.deviantart.com/) (CC BY 3.0)
    - [voodoo_cactus_underwater by lzubiaur](https://opengameart.org/node/30946) (CC BY 3.0)
- music:
    - summer_sunday (CC0): [Summer Sunday by celestialghost8](https://opengameart.org/node/71806)
- font:
    - [Press Start 2P Medium (OFL)](https://fontlibrary.org/font/press-start-2p)
    - details: size 8, no antialiasing

---
## Building

### Bundled Libraries

- [cxxopts](https://github.com/jarro2783/cxxopts) v3.2.0 ([MIT](lib/cxxopts/LICENSE.txt))
- [lua](https://lua.org/) v5.4.7 ([MIT](lib/lua/LICENSE.txt)) _(disabled)_

### External Libraries

- [SDL2](https://libsdl.org/) (zlib) ([source](https://github.com/libsdl-org/SDL/releases))
- [SDL2_mixer](https://wiki.libsdl.org/SDL2_mixer) (zlib) ([source](https://github.com/libsdl-org/SDL_mixer/releases))
- [SDL2_image](https://wiki.libsdl.org/SDL2_image) (zlib) ([source](https://github.com/libsdl-org/SDL_image/releases))
- [TinyXML-2](http://leethomason.github.io/tinyxml2/) (zlib) ([source](https://github.com/leethomason/tinyxml2/releases))
- [tmxlite](https://github.com/fallahn/tmxlite) (zlib)

### Required Build Tools

- GNU compatible C++ compiler such as [gcc](https://www.gnu.org/software/gcc/) or
    [clang](https://clang.llvm.org/) with C++20 support.
- [CMake](https://cmake.org/)

### Running CMake Commands

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

__CMake Options:__

- `-DDEBUG=on`: Enable debugging symbols.
- `-DSTATIC=off`: Disable linking executable statically by default.
- `-DEXAMPLE=on`: Copy example game data files to build directory.

---
## Building Documentation

Documentation is built using [MkDocs](https://www.mkdocs.org/). You will need to install
[Python](https://python.org/) & the `mkdocs` module:

```
$ python -m pip install mkdocs
```

Run `mkdocs build` from root directory. To preview documenation run `mkdocs serve` then
open http://localhost:8000/ in a web browser.

---
## Links

- [TODO](TODO.md)
