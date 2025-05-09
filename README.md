
# R&R Engine (Rock & Roll Engine)

---
## Description

_(this software is a work-in-progress & not yet fully functional)_

An engine to create [Mega Man/Rockman](https://en.wikipedia.org/wiki/Mega_Man) style platform games.

_This project is not affiliated an any way with Capcom. Nor is it related to the fan game known as
[Mega Man: Rock N Roll](https://megamanfanon.fandom.com/wiki/Mega_Man:_Rock_N_Roll)._

---
## Licensing

Source: [MIT](LICENSE.txt)

Example data:

- sprite:
    - character (CC0): based on [Mega Bot Assets Pack by Luis Zuno (ansimuz)](https://opengameart.org/node/99323)
    - enemy (CC0): [Classic Hero and Baddies Pack by GrafxKid](https://opengameart.org/node/36173)
    - flying_enemy (CC0): [Mega Bot Assets Pack by Luis Zuno (ansimuz)](https://opengameart.org/node/99323)
    - explosion (CC0): [Mega Bot Assets Pack by Luis Zuno (ansimuz)](https://opengameart.org/node/99323)
- tileset:
    - megabot (CC0): [Mega Bot Assets Pack by Luis Zuno (ansimuz)](https://opengameart.org/node/99323)
- backgrounds:
    - megabot_scaled* (CC0): [Mega Bot Assets Pack by Luis Zuno (ansimuz)](https://opengameart.org/node/99323)
    - [voodoo_cactus_underwater by lzubiaur](https://opengameart.org/node/30946) (CC BY 3.0)
- music:
    - [actiontheme-v3 by Ted Kerr](https://opengameart.org/node/150692) (CC BY 4.0)
    - summer_sunday (CC0): [Summer Sunday by celestialghost8](https://opengameart.org/node/71806)
- font:
    - [Press Start 2P Medium (OFL)](https://fontlibrary.org/font/press-start-2p)
    - details: size 8, no antialiasing

---
## Building

### Bundled Libraries

- [cxxopts](https://github.com/jarro2783/cxxopts) v3.2.0 ([MIT](lib/cxxopts/LICENSE.txt))
- [lua](https://lua.org/) v5.4.7 ([MIT](lib/lua/LICENSE.txt)) _(disabled)_
- [tmxlite](https://github.com/fallahn/tmxlite) v1.4.4 (zlib)

### External Libraries

- [SDL2](https://libsdl.org/) (zlib) ([source](https://github.com/libsdl-org/SDL/releases))
- [SDL2_mixer](https://wiki.libsdl.org/SDL2_mixer) (zlib) ([source](https://github.com/libsdl-org/SDL_mixer/releases))
- [SDL2_image](https://wiki.libsdl.org/SDL2_image) (zlib) ([source](https://github.com/libsdl-org/SDL_image/releases))
- [pugixml](https://pugixml.org/) (MIT) ([source](https://github.com/zeux/pugixml))

### Required Build Tools

- GNU compatible C++ compiler such as [gcc](https://www.gnu.org/software/gcc/) or
  [clang](https://clang.llvm.org/) with C++20 support (untested with other compilers).
- [CMake](https://cmake.org/)
- [pkg-config](https://www.freedesktop.org/wiki/Software/pkg-config/) or [pkgconf](http://pkgconf.org/)

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

__Build Options:__

The following are notable build options that can be configured using CMake's `-D` flag. Example:
`cmake -B build -DSTATIC=ON`.

CMake standard options:

- `CMAKE_BUILD_TYPE`: Set to `Release` for optimized build without debugging symbols. Default:
  `Debug`.
- `CMAKE_CXX_STANDARD`: Standard to use for C++ code compilation. Minimum supported is 20. Default:
  `20`.
- `CMAKE_C_STANDARD`: Standard to use for C code compilation. Default: compiler default.

Project specific options:

- `EXAMPLE`: Copy example game data files to build directory. Default: `OFF`.
- `STATIC`: Link dependency libraries statically. Default: `OFF`.
- `SYSTEM_TMXLITE`: Use system's tmxlite library instead of building bundled version. Default:
  `OFF`.
- `BIN2HEADER`: Path to [`Binary to Header`](https://antumdeluge.github.io/bin2header/) executable.
  Used for converting built-in resources. Default: auto detected.
- `FFMPEG`: Path to [`FFmpeg`](https://ffmpeg.org/) executable. Used for converting example music
  data. Default: auto detected.

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

- Source code:
    - [Codeberg](https://codeberg.org/AntumDeluge/RREngine)
    - [GitHub](https://github.com/AntumDeluge/RREngine)
- [TODO](TODO.md)
