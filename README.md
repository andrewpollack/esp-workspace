# ESP Workspace

Personal ESP32 monorepo using ESP-IDF. Multiple firmware projects share a single SDK.

## Setup (macOS Apple Silicon)

```bash
brew install cmake ninja python
make esp-idf                       # Clone and pin ESP-IDF
cd esp-idf && ./install.sh         # Install toolchains (one-time)
```

## Usage

Activate ESP-IDF environment (or use direnv with `.envrc`):
```bash
source ./esp-idf/export.sh
```

Build and flash from any project directory:
```bash
idf.py build
idf.py flash monitor
```

Create a new project:
```bash
idf.py create-project esp32-my-project
cd esp32-my-project
idf.py set-target esp32
```

## Structure

- `esp-idf/` - SDK (gitignored, pinned via `esp-idf.commit`)
- `esp32-*/` - Standalone projects
- `common/` - Shared components

Shared component layout:
```
common/my_component/
├── CMakeLists.txt
├── include/my_component.h
└── my_component.c
```

Include in a project's `CMakeLists.txt`:
```cmake
set(EXTRA_COMPONENT_DIRS ${CMAKE_CURRENT_LIST_DIR}/../common)
```

## References

- [ESP-IDF Repository](https://github.com/espressif/esp-idf)
- [ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf/)
