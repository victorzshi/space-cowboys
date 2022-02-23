# Space Cowboys

![GitHub Actions](https://github.com/victorzshi/space-cowboys/actions/workflows/github-actions.yml/badge.svg)

Original C++ game inspired by Taito's Space Invaders (1978).

![Gameplay](space-cowboys.gif)

## How to Play

Download and extract [space-cowboys-0.1.1-win64.zip](https://github.com/victorzshi/space-cowboys/releases/download/v0.1.1/space-cowboys-0.1.1-win64.zip).

Inside the folder **bin/src/**, run `main.exe`.

- Use the arrow keys to move and space to fire.
- Press F to toggle fullscreen.
- Press R to restart the game.

If the windowed mode is too large, disable DPI scaling on `main.exe`: Right click > Properties > Compatibility > Change high DPI settings > Check "Override high DPI scaling behaviour" > Select "Application" from the drop down.

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
cmake -B build
cmake --build build
```

## About

Graphics provided by [Twemoji](https://twemoji.twitter.com/).

ASCII art provided by [Text to ASCII Art Generator](https://patorjk.com/software/taag/).

## License

[MIT](https://choosealicense.com/licenses/mit/)
