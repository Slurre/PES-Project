cmake_minimum_required(VERSION 3.10)

project(dynamic_code-base C CXX ASM)

include(../common.cmake)

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

# NRF SDK
add_library(nrf-sdk STATIC ${SDK_SOURCE_FILES})
target_include_directories(nrf-sdk SYSTEM PUBLIC . ../../)
target_include_directories(nrf-sdk SYSTEM PUBLIC ${INCLUDES_FROM_LIBS})
target_compile_options(nrf-sdk PRIVATE
        $<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:DEBUG>>: ${COMMON_FLAGS} -Wno-expansion-to-defined -Og -g3>
        $<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:RELEASE>>: ${COMMON_FLAGS} -Wno-expansion-to-defined -O3>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:DEBUG>>: ${COMMON_FLAGS} -Wno-expansion-to-defined -Og -fno-rtti>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:RELEASE>>: ${COMMON_FLAGS} -Wno-expansion-to-defined -O3 -fno-rtti>
        $<$<COMPILE_LANGUAGE:ASM>: -MP -MD -x assembler-with-cpp>
        )

# Build autonomous binary (without support for bootloader)
set(EXECUTABLE_NAME "dynamic_code-base")
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
        COMMAND ${CMAKE_NM} ${EXECUTABLE_FILE_NAME}.out | sed -e 's/\\\([0-9a-f]*\\\) . \\\(.*\\\)/\\2 = 0x\\1;/' > "${EXECUTABLE_FILE_NAME}.syms"
        COMMENT "post build steps for ${EXECUTABLE_FILE_NAME}")
