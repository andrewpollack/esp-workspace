# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

This is a personal ESP32 monorepo using ESP-IDF. Multiple firmware projects share a single SDK installation. The `esp-idf/` directory is gitignored and treated as a local SDK.

## Setup Commands

```bash
# Initial setup (clone and pin ESP-IDF)
make esp-idf

# Verify ESP-IDF is at expected commit
make check-esp-idf

# Update pinned commit after upgrading ESP-IDF
make update-esp-idf
```

## Build Commands

From inside any project directory (`esp32-*/`):

```bash
idf.py build              # Build firmware
idf.py flash monitor      # Flash and open serial monitor
idf.py set-target esp32   # Set target chip (esp32, esp32s3, etc.)
idf.py menuconfig         # Configure project options
```

From repo root:
```bash
idf.py create-project esp32-<name>  # Create new project
```

## Architecture

- **esp-idf/**: ESP-IDF SDK (gitignored, pinned via `esp-idf.commit`)
- **esp32-*/**: Standalone ESP-IDF projects (each has `CMakeLists.txt` + `main/`)
- **common/**: Shared ESP-IDF components (include via `EXTRA_COMPONENT_DIRS` in project CMakeLists.txt)

## Environment

The `.envrc` auto-sources `esp-idf/export.sh` via direnv. Without direnv, manually run:
```bash
source ./esp-idf/export.sh
```

## Key Files

- `esp-idf.commit`: Pinned ESP-IDF commit hash for reproducibility
- `Makefile`: SDK management (clone, verify, update)

## Commit Style

Use [Conventional Commits](https://www.conventionalcommits.org/):

```
feat: new feature
fix(scope): bug in scope
feat!: breaking change
chore(deps): update dependencies
```

Types: `feat`, `fix`, `chore`, `docs`, `build`, `ci`, `perf`, `refactor`, `revert`, `style`, `test`
