cmake_minimum_required(VERSION 3.15)

project(yaml-parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# ==============================================================================

include(FetchContent)
FetchContent_Declare(
  rapidyaml
  GIT_REPOSITORY https://github.com/biojppm/rapidyaml.git
  GIT_TAG master)

FetchContent_Declare(
  c4fs
  GIT_REPOSITORY https://github.com/biojppm/c4fs.git
  GIT_TAG master)

FetchContent_MakeAvailable(rapidyaml c4fs)

# ==============================================================================

add_executable(pre_commit_hook_parser parser.cpp)
target_link_libraries(pre_commit_hook_parser PUBLIC c4fs ryml)

# ==============================================================================

include(GNUInstallDirs)

install(TARGETS pre_commit_hook_parser RUNTIME)
install(PROGRAMS scripts/pre-commit
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/bash-completion/completions)
