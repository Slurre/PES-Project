cmake_minimum_required(VERSION 3.10)
project(dynamic_code VERSION 0.0.1 LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)

# set(CMAKE_GENERATOR "Unix Makefiles")
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(NRF_TARGET "nrf52")

if (NOT ARM_NONE_EABI_TOOLCHAIN_PATH)
  message(FATAL_ERROR "The path to the toolchain (arm-none-eabi) must be specified on the command line (add -DARM_NONE_EABI_TOOLCHAIN_PATH=<path>")
endif ()

if (NOT NRF5_SDK_PATH)
  message(FATAL_ERROR "The path to the NRF52 SDK must be specified on the command line (add -DNRF5_SDK_PATH=<path>")
endif ()

add_subdirectory(src)
