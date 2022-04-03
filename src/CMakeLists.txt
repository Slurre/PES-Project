cmake_minimum_required(VERSION 3.10)

project(dynamic_code-app C CXX ASM)


# define some variables just for this example to determine file locations
set(NRF_PROJECT_NAME dynamic_code-app)
set(NRF_CHIP NRF52840)
set(NRF_BOARD PCA10056) #changed for devkit stub

# check if all the necessary tools paths have been provided.
if (NOT NRF5_SDK_PATH)
    message(FATAL_ERROR "The path to the nRF5 SDK (NRF5_SDK_PATH) must be set.")
endif ()
if (DEFINED ARM_NONE_EABI_TOOLCHAIN_PATH)
    set(ARM_NONE_EABI_TOOLCHAIN_BIN_PATH ${ARM_NONE_EABI_TOOLCHAIN_PATH}/bin)
endif ()

if (NOT NRF_TARGET MATCHES "nrf52")
    message(FATAL_ERROR "Only rRF52 boards are supported right now")
endif ()

# Setup toolchain
include(${CMAKE_SOURCE_DIR}/arm-gcc-toolchain.cmake)

if (NOT DEFINED ARM_GCC_TOOLCHAIN)
    message(FATAL_ERROR "The toolchain must be set up before calling this macro")
endif ()
set(CMAKE_OSX_SYSROOT "/")
set(CMAKE_OSX_DEPLOYMENT_TARGET "")


set(SDK_SOURCE_FILES
        # Startup
        "${NRF5_SDK_PATH}/modules/nrfx/mdk/system_nrf52.c"
        "${NRF5_SDK_PATH}/modules/nrfx/mdk/gcc_startup_nrf52.S"

        # Base SDK
        "${NRF5_SDK_PATH}/components/boards/boards.c"
        "${NRF5_SDK_PATH}/integration/nrfx/legacy/nrf_drv_clock.c"
        "${NRF5_SDK_PATH}/integration/nrfx/legacy/nrf_drv_clock.h"
        "${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_clock.c"
        "${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_gpiote.c"
        "${NRF5_SDK_PATH}/modules/nrfx/soc/nrfx_atomic.c"
        "${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_saadc.c"
        "${NRF5_SDK_PATH}/components/libraries/timer/app_timer.h"

        # Libs
        "${NRF5_SDK_PATH}/components/libraries/atomic/nrf_atomic.c"
        "${NRF5_SDK_PATH}/components/libraries/balloc/nrf_balloc.c"
        "${NRF5_SDK_PATH}/components/libraries/util/nrf_assert.c"
        "${NRF5_SDK_PATH}/components/libraries/util/app_error.c"
        "${NRF5_SDK_PATH}/components/libraries/util/app_error_weak.c"
        "${NRF5_SDK_PATH}/components/libraries/util/app_error_handler_gcc.c"
        "${NRF5_SDK_PATH}/components/libraries/util/app_util_platform.c"
        "${NRF5_SDK_PATH}/components/libraries/log/src/nrf_log_backend_rtt.c"
        "${NRF5_SDK_PATH}/components/libraries/log/src/nrf_log_backend_serial.c"
        "${NRF5_SDK_PATH}/components/libraries/log/src/nrf_log_default_backends.c"
        "${NRF5_SDK_PATH}/components/libraries/log/src/nrf_log_frontend.c"
        "${NRF5_SDK_PATH}/components/libraries/log/src/nrf_log_str_formatter.c"
        "${NRF5_SDK_PATH}/components/libraries/memobj/nrf_memobj.c"
        "${NRF5_SDK_PATH}/components/libraries/ringbuf/nrf_ringbuf.c"
        "${NRF5_SDK_PATH}/components/libraries/strerror/nrf_strerror.c"

        # Segger RTT
        "${NRF5_SDK_PATH}/external/segger_rtt/SEGGER_RTT_Syscalls_GCC.c"
        "${NRF5_SDK_PATH}/external/segger_rtt/SEGGER_RTT.c"
        "${NRF5_SDK_PATH}/external/segger_rtt/SEGGER_RTT_printf.c"

        # Other
        "${NRF5_SDK_PATH}/external/utf_converter/utf.c"
        "${NRF5_SDK_PATH}/external/fprintf/nrf_fprintf.c"
        "${NRF5_SDK_PATH}/external/fprintf/nrf_fprintf_format.c"

        # TWI
        "${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_twim.c"

        # GPIOTE
        "${NRF5_SDK_PATH}/components/libraries/gpiote/app_gpiote.c"
        )

list(APPEND SOURCE_FILES
        main.c
)


set(INCLUDE_FILES
)

include_directories(
        ${CMAKE_BINARY_DIR}/src # include generated files like Version.h
        .
        ../

        "${NRF5_SDK_PATH}/components/drivers_nrf/nrf_soc_nosd"
        "${NRF5_SDK_PATH}/components"
        "${NRF5_SDK_PATH}/components/boards"
        "${NRF5_SDK_PATH}/components/softdevice/common"
        "${NRF5_SDK_PATH}/integration/nrfx"
        "${NRF5_SDK_PATH}/integration/nrfx/legacy"
        "${NRF5_SDK_PATH}/modules/nrfx"
        "${NRF5_SDK_PATH}/modules/nrfx/drivers/include"
        "${NRF5_SDK_PATH}/modules/nrfx/hal"
        "${NRF5_SDK_PATH}/modules/nrfx/mdk"
        "${NRF5_SDK_PATH}/external/freertos/source/include"
        "${NRF5_SDK_PATH}/components/toolchain/cmsis/include"
        "${NRF5_SDK_PATH}/components/libraries/atomic"
        "${NRF5_SDK_PATH}/components/libraries/atomic_fifo"
        "${NRF5_SDK_PATH}/components/libraries/atomic_flags"
        "${NRF5_SDK_PATH}/components/libraries/balloc"
        "${NRF5_SDK_PATH}/components/libraries/bootloader/ble_dfu"
        "${NRF5_SDK_PATH}/components/libraries/cli"
        "${NRF5_SDK_PATH}/components/libraries/crc16"
        "${NRF5_SDK_PATH}/components/libraries/crc32"
        "${NRF5_SDK_PATH}/components/libraries/crypto"
        "${NRF5_SDK_PATH}/components/libraries/csense"
        "${NRF5_SDK_PATH}/components/libraries/csense_drv"
        "${NRF5_SDK_PATH}/components/libraries/delay"
        "${NRF5_SDK_PATH}/components/libraries/ecc"
        "${NRF5_SDK_PATH}/components/libraries/experimental_section_vars"
        "${NRF5_SDK_PATH}/components/libraries/experimental_task_manager"
        "${NRF5_SDK_PATH}/components/libraries/fds"
        "${NRF5_SDK_PATH}/components/libraries/fstorage"
        "${NRF5_SDK_PATH}/components/libraries/gfx"
        "${NRF5_SDK_PATH}/components/libraries/gpiote"
        "${NRF5_SDK_PATH}/components/libraries/hardfault"
        "${NRF5_SDK_PATH}/components/libraries/hci"
        "${NRF5_SDK_PATH}/components/libraries/led_softblink"
        "${NRF5_SDK_PATH}/components/libraries/log"
        "${NRF5_SDK_PATH}/components/libraries/log/src"
        "${NRF5_SDK_PATH}/components/libraries/low_power_pwm"
        "${NRF5_SDK_PATH}/components/libraries/mem_manager"
        "${NRF5_SDK_PATH}/components/libraries/memobj"
        "${NRF5_SDK_PATH}/components/libraries/mpu"
        "${NRF5_SDK_PATH}/components/libraries/mutex"
        "${NRF5_SDK_PATH}/components/libraries/pwm"
        "${NRF5_SDK_PATH}/components/libraries/pwr_mgmt"
        "${NRF5_SDK_PATH}/components/libraries/queue"
        "${NRF5_SDK_PATH}/components/libraries/ringbuf"
        "${NRF5_SDK_PATH}/components/libraries/scheduler"
        "${NRF5_SDK_PATH}/components/libraries/sdcard"
        "${NRF5_SDK_PATH}/components/libraries/slip"
        "${NRF5_SDK_PATH}/components/libraries/sortlist"
        "${NRF5_SDK_PATH}/components/libraries/spi_mngr"
        "${NRF5_SDK_PATH}/components/libraries/stack_guard"
        "${NRF5_SDK_PATH}/components/libraries/strerror"
        "${NRF5_SDK_PATH}/components/libraries/svc"
        "${NRF5_SDK_PATH}/components/libraries/timer"
        "${NRF5_SDK_PATH}/components/libraries/usbd"
        "${NRF5_SDK_PATH}/components/libraries/usbd/class/audio"
        "${NRF5_SDK_PATH}/components/libraries/usbd/class/cdc"
        "${NRF5_SDK_PATH}/components/libraries/usbd/class/cdc/acm"
        "${NRF5_SDK_PATH}/components/libraries/usbd/class/hid"
        "${NRF5_SDK_PATH}/components/libraries/usbd/class/hid/generic"
        "${NRF5_SDK_PATH}/components/libraries/usbd/class/hid/kbd"
        "${NRF5_SDK_PATH}/components/libraries/usbd/class/hid/mouse"
        "${NRF5_SDK_PATH}/components/libraries/usbd/class/msc"
        "${NRF5_SDK_PATH}/components/libraries/util"
        "${NRF5_SDK_PATH}/external/segger_rtt/"
        "${NRF5_SDK_PATH}/external/fprintf/"
        "${NRF5_SDK_PATH}/external/thedotfactory_fonts"
        "${NRF5_SDK_PATH}/components/libraries/gpiote"

)

link_directories(
        ../
)


set(COMMON_FLAGS -MP -MD -mthumb -mabi=aapcs -Wall -Wextra -Warray-bounds=2 -Wformat=2 -Wformat-overflow=2 -Wformat-truncation=2 -Wformat-nonliteral -ftree-vrp -Wno-unused-parameter -Wno-missing-field-initializers -Wno-unknown-pragmas -Wno-expansion-to-defined -g3 -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin --short-enums -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Wreturn-type -Werror=return-type -fstack-usage -fno-exceptions -fno-non-call-exceptions)
add_definitions(-DCONFIG_GPIO_AS_PINRESET)
add_definitions(-DOS_CPUTIME_FREQ)
add_definitions(-DNRF52 -D${NRF_CHIP} -D${NRF_CHIP}_XXAA -DNRF52_PAN_74 -DNRF52_PAN_64 -DNRF52_PAN_12 -DNRF52_PAN_58 -DNRF52_PAN_54 -DNRF52_PAN_31 -DNRF52_PAN_51 -DNRF52_PAN_36 -DNRF52_PAN_15 -DNRF52_PAN_20 -DNRF52_PAN_55 -DBOARD_${NRF_BOARD})
add_definitions(-D__STACK_SIZE=1024)
add_definitions(-D__HEAP_SIZE=4096)

# NOTE : Add the following defines to enable debug mode of the NRF SDK:
#add_definitions(-DDEBUG)
#add_definitions(-DDEBUG_NRF_USER)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif ()

# NRF SDK
add_library(nrf-sdk STATIC ${SDK_SOURCE_FILES})
target_include_directories(nrf-sdk SYSTEM PUBLIC . ../)
target_include_directories(nrf-sdk SYSTEM PUBLIC ${INCLUDES_FROM_LIBS})
target_compile_options(nrf-sdk PRIVATE
        $<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:DEBUG>>: ${COMMON_FLAGS} -Wno-expansion-to-defined -Og -g3>
        $<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:RELEASE>>: ${COMMON_FLAGS} -Wno-expansion-to-defined -O3>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:DEBUG>>: ${COMMON_FLAGS} -Wno-expansion-to-defined -Og -fno-rtti>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:RELEASE>>: ${COMMON_FLAGS} -Wno-expansion-to-defined -O3 -fno-rtti>
        $<$<COMPILE_LANGUAGE:ASM>: -MP -MD -x assembler-with-cpp>
        )

# Build autonomous binary (without support for bootloader)
set(EXECUTABLE_NAME "dynamic_code-app")
set(EXECUTABLE_FILE_NAME ${EXECUTABLE_NAME})
set(NRF5_LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/gcc_nrf52.ld")
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})
set_target_properties(${EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME ${EXECUTABLE_FILE_NAME})
target_link_libraries(${EXECUTABLE_NAME} nrf-sdk)
target_compile_options(${EXECUTABLE_NAME} PUBLIC
        $<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:DEBUG>>: ${COMMON_FLAGS} -Wextra -Wformat -Wno-missing-field-initializers -Wno-unused-parameter -Og -g3>
        $<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:RELEASE>>: ${COMMON_FLAGS} -Wextra -Wformat -Wno-missing-field-initializers -Wno-unused-parameter -Os>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:DEBUG>>: ${COMMON_FLAGS} -Wextra -Wformat -Wno-missing-field-initializers -Wno-unused-parameter -Og -g3 -fno-rtti>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:RELEASE>>: ${COMMON_FLAGS} -Wextra -Wformat -Wno-missing-field-initializers -Wno-unused-parameter -Os -fno-rtti>
        $<$<COMPILE_LANGUAGE:ASM>: -MP -MD -x assembler-with-cpp>
        )

set_target_properties(${EXECUTABLE_NAME} PROPERTIES
        SUFFIX ".out"
        LINK_FLAGS "-mthumb -mabi=aapcs -L ${NRF5_SDK_PATH}/modules/nrfx/mdk -T${NRF5_LINKER_SCRIPT} -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Wl,--gc-sections -Wl,--print-memory-usage --specs=nano.specs -lc -lnosys -lm -Wl,-Map=${EXECUTABLE_FILE_NAME}.map"
        )

add_custom_command(TARGET ${EXECUTABLE_NAME}
        POST_BUILD
        COMMAND ${CMAKE_SIZE_UTIL} ${EXECUTABLE_FILE_NAME}.out
        COMMAND ${CMAKE_OBJCOPY} -O binary ${EXECUTABLE_FILE_NAME}.out "${EXECUTABLE_FILE_NAME}.bin"
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${EXECUTABLE_FILE_NAME}.out "${EXECUTABLE_FILE_NAME}.hex"
        COMMENT "post build steps for ${EXECUTABLE_FILE_NAME}")
