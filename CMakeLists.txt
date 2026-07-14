cmake_minimum_required(VERSION 3.20)

project(gbafire LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(gbafire
  src/main.cpp
  src/core/Fire.cpp
)

target_include_directories(gbafire
  PRIVATE
  "${CMAKE_SOURCE_DIR}/src"
)

target_compile_features(gbafire PRIVATE cxx_std_17)

target_compile_options(gbafire PRIVATE
  -fno-exceptions
  -fno-rtti
)

gba_create_rom(gbafire
  TITLE "GBAFire"
)
