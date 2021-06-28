# pre-commit-completion

This repository contains a BASH completion script for pre-commit as well as the code for a small executable that is aimed at extracting the list of hooks that can be found in a `.pre-commit-config.yaml` file.

## Build

Building this project should be as simple as running CMake

    cmake -S path/to/this/repository -B build

and then building the main executable

    cmake --build build --target pre_commit_hook_parser


## Installation

Installing the script and hook parser on your system can be done directly using CMake:

    cmake --build build --target install

which would install:

- `pre_commit_hook_parser` in `<prefix>/bin`
- `pre_commit` in `<prefix>/share/bash-completion/completions/`

where `<prefix>` can be customized using the `CMAKE_INSTALL_PREFIX` CMake variable.
