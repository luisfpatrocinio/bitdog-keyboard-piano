# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(FirstHDMI C CXX ASM)

# PatroLibs 01

include(FetchContent)

FetchContent_Declare(
  bitdoglibs
  GIT_REPOSITORY https://github.com/luisfpatrocinio/bitdog-patroLibs.git
  GIT_TAG main
)

FetchContent_MakeAvailable(bitdoglibs)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(FirstHDMI main.c )

pico_set_program_name(FirstHDMI "FirstHDMI")
pico_set_program_version(FirstHDMI "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(FirstHDMI 0)
pico_enable_stdio_usb(FirstHDMI 1)

# Add the standard library to the build
target_link_libraries(FirstHDMI
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(FirstHDMI PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(FirstHDMI 
        
        )

pico_add_extra_outputs(FirstHDMI)

target_link_libraries(FirstHDMI
    bitdog::patrolibs
)