# Space Invaders (WIP)

C++ clone of Taito's arcade game Space Invaders (1978).

> TODO: Add gameplay gif.

## Installation

Clone repo:
```
git clone https://github.com/victorzshi/space-invaders.git
```

Initialize submodules inside **external/**:
```
git submodule init
git submodule update
```

Bootstrap vcpkg package manager:
```
# Windows
.\external\vcpkg\bootstrap-vcpkg.bat -disableMetrics
# Unix
./external/vcpkg/bootstrap-vcpkg.sh -disableMetrics
```

Install dependencies:
```
# Windows
.\external\vcpkg\vcpkg install
# Unix
./external/vcpkg/vcpkg install
```

## Known Issues

Errors while running CTest for `Ninja Multi-Config`:

```
Test not available without configuration.  (Missing "-C <config>"?)
```

> See [open issue](https://gitlab.kitware.com/cmake/cmake/-/issues/20283). Catch2 tests are unaffected.

## License

[MIT](https://choosealicense.com/licenses/mit/)
