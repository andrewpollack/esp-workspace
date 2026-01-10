# ESP Workspace

Personal ESP32 monorepo using ESP-IDF. Multiple firmware projects share a single SDK.

## Setup (macOS Apple Silicon)

```bash
brew install cmake ninja python
make esp-idf                       # Clone and pin ESP-IDF
cd esp-idf && ./install.sh         # Install toolchains (one-time)
make secrets                       # Create secrets.cmake for WiFi
```

Edit `secrets.cmake` with your WiFi credentials:
```cmake
set(WIFI_SSID "your_network")
set(WIFI_PASSWORD "your_password")
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
  - `logging/` - Log wrapper (`log_info`, `log_warn`, `log_error`)
  - `wifi/` - WiFi connection (credentials from `secrets.cmake`)

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
