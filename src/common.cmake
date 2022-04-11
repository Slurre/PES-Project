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

set(INCLUDE_FILES
)

include_directories(
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
