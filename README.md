# ESP Workspace (Personal Monorepo)

This repository is a **personal ESP32 workspace / monorepo** built around
Espressif’s **ESP-IDF**. It is designed for learning, experimentation, and
building multiple firmware projects with a single shared SDK.

This is **not** a single product repo. It is a workspace.

---

## Goals

- One shared ESP-IDF installation
- Many independent ESP projects
- Clean git history (no build output, no SDK commits)
- Fast iteration and low friction
- Explicit, understandable setup

---

## Directory Layout

    esp/
    ├── esp-idf/              # ESP-IDF SDK (local install, NOT committed)
    ├── esp32-hello/          # Example project
    ├── esp32-wifi-logger/    # Project
    ├── esp32-rtos-playground # Project
    ├── common/               # Shared ESP-IDF components
    ├── .gitignore
    └── README.md

### Rules

- `esp-idf/` is **ignored by git**
- Each `esp32-*` directory is a **standalone ESP-IDF project**
- Projects are intentionally **flattened at the top level**
- Shared code lives in `common/` as proper ESP-IDF components

---

## ESP-IDF Setup (Required)

This workspace expects ESP-IDF to live at:

    ~/esp/esp-idf

### 1. Install system prerequisites

On macOS (Apple Silicon supported natively):

```bash
brew install cmake ninja python
```

### 2. Clone ESP-IDF into this repo

From the root of this repository:
```bash
git clone --recursive https://github.com/espressif/esp-idf.git esp-idf
```

`esp-idf/` is intentionally not committed.
It is treated as a local SDK installation, similar to `/opt` or `/usr/local`.

### 3. Install ESP-IDF toolchains

```bash
cd esp-idf
./install.sh
```

This installs:
- Xtensa and RISC-V cross-compilers
- Python tooling (idf.py, esptool.py)
- GDB and OpenOCD

This step is one-time per machine.

### 4. Activate the ESP-IDF environment

Before working on any project, run:

```bash
source ~/esp/esp-idf/export.sh
```

This sets:
- `IDF_PATH`
- `PATH` (toolchains and `idf.py`)
- Python venv

Verify:
```bash
idf.py --version
```

## Creating a new project

From the repo root:

```bash
idf.py create-project esp32-my-project
cd esp32-my-project
idf.py set-target esp32
idf.py build
```

Each project must contain:
- `CMakeLists.txt`
- `main/`

## Building, Flashing, Monitoring

From inside a project directory:
```bash
idf.py build
idf.py flash monitor
```

## Shared Code (`common/`)

Reusable code should be written as ESP-IDF components, not copied files or
symlinks.
Example layout:
```
common/my_logging/
├── CMakeLists.txt
├── include/
│   └── my_logging.h
└── my_logging.c
```

In a project's `CMakeLists.txt`:
```cmake
set(EXTRA_COMPONENT_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/../common
)
```

## sdkconfig

sdkconfig is intentionally not committed in this workspace-style repo.

If reproducibility is needed later:
```bash
idf.py save-defconfig
```

## References

- ESP-IDF repository: https://github.com/espressif/esp-idf
- ESP-IDF Programming Guide: https://docs.espressif.com/projects/esp-idf/

