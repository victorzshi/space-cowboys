# Space Cowboys

![GitHub Actions](https://github.com/victorzshi/space-cowboys/actions/workflows/github-actions.yml/badge.svg)

Original C++ game inspired by Taito's Space Invaders (1978).

![Gameplay](space-cowboys.gif)

## How to Play

Download and extract [space-cowboys-0.1.2-win64.zip](https://github.com/victorzshi/space-cowboys/releases/download/v0.1.2/space-cowboys-0.1.2-win64.zip).

Inside the folder **bin/src/**, run `main.exe`.

- Use WASD or the arrow keys to move and SPACE to fire.
- Press ESC to pause the game.
- Press R to restart the game.
- Press F to toggle fullscreen.
- Press V to disable vertical sync (only on start screen).

If the windowed mode is too large, you have two options:

1. Disable DPI scaling.
   > On Windows 11: Right click on `main.exe` > Properties > Compatibility > Change high DPI settings > Check "Override high DPI scaling behaviour" > Select "Application" from the drop down.
2. Use fullscreen mode.

## Installation

Clone repo:

```
git clone https://github.com/victorzshi/space-cowboys.git
```

Initialize submodules:

```
git submodule init
git submodule update
```

Build with CMake:

```
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="external/vcpkg/scripts/buildsystems/vcpkg.cmake"
cmake --build build
```

## About

Graphics provided by [Twemoji](https://twemoji.twitter.com/).

ASCII art provided by [Text to ASCII Art Generator](https://patorjk.com/software/taag/).

## License

[MIT](https://choosealicense.com/licenses/mit/)
