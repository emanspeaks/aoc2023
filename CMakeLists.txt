cmake_minimum_required(VERSION 3.21.0)
project(aoc2023
  VERSION 0.1.0
  DESCRIPTION "Advent of Code 2023"
  HOMEPAGE_URL https://github.com/emanspeaks/aoc2023
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

## configure CMake module search paths that depend on the project
## proj src dir is location of this file
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(CompileCommands)
include(DefaultBuildType)
include(DefaultInstallPath)
include(ForceUnicode)
include(DefineWindows)
include(HideVSCodeVars)

add_compile_definitions(AOCDEBUG)

add_subdirectory(libaoc)
add_subdirectory(day01)
add_subdirectory(day02)
add_subdirectory(day03)
add_subdirectory(day04)
add_subdirectory(day05)
add_subdirectory(day06)
add_subdirectory(day07)
add_subdirectory(day08)
add_subdirectory(day09)
add_subdirectory(day10)
add_subdirectory(day11)
add_subdirectory(day12)
add_subdirectory(day13)
add_subdirectory(day14)
add_subdirectory(day15)
add_subdirectory(day16)
add_subdirectory(day17)
add_subdirectory(day18)
#add_subdirectory(day19)
#add_subdirectory(day20)
#add_subdirectory(day21)
#add_subdirectory(day22)
#add_subdirectory(day23)
#add_subdirectory(day24)
#add_subdirectory(day25)
