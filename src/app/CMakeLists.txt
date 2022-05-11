cmake_minimum_required(VERSION 3.10)

project(dynamic_code-app C CXX ASM)

include(../common.cmake)

list(APPEND SOURCE_FILES
        main.cpp
)

# Build app binary (statically linked against symbol definition file)
set(APP_STUB "dynamic_code-app+stub")
set(APP_REAL "dynamic_code-app")
set(COMMON_LINK_FLAGS "-mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16 -T${CMAKE_SOURCE_DIR}/src/app/app.ld -Wl,--gc-sections -Wl,--print-memory-usage --specs=nano.specs -lc -lnosys -lm")

foreach(EXECUTABLE_NAME IN ITEMS ${APP_STUB} ${APP_REAL})
set(EXECUTABLE_FILE_NAME ${EXECUTABLE_NAME})
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})
set_target_properties(${EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME ${EXECUTABLE_FILE_NAME})
#set(COMMON_FLAGS ${COMMON_FLAGS} -fPIC -mpic-register=r9 -msingle-pic-base -mno-pic-data-is-text-relative -fPIE)
target_compile_options(${EXECUTABLE_NAME} PUBLIC
        $<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:DEBUG>>: ${COMMON_FLAGS} -Wextra -Wformat -Wno-missing-field-initializers -Wno-unused-parameter -Og -g3>
        $<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:RELEASE>>: ${COMMON_FLAGS} -Wextra -Wformat -Wno-missing-field-initializers -Wno-unused-parameter -Os>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:DEBUG>>: ${COMMON_FLAGS} -Wextra -Wformat -Wno-missing-field-initializers -Wno-unused-parameter -Og -g3 -fno-rtti>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:RELEASE>>: ${COMMON_FLAGS} -Wextra -Wformat -Wno-missing-field-initializers -Wno-unused-parameter -Os -fno-rtti>
        $<$<COMPILE_LANGUAGE:ASM>: -MP -MD -x assembler-with-cpp>
        )
endforeach()

set(EXECUTABLE_NAME ${APP_STUB})
set(EXECUTABLE_FILE_NAME ${EXECUTABLE_NAME})
set_target_properties(${EXECUTABLE_NAME} PROPERTIES
        SUFFIX ".out"
        LINK_FLAGS "${COMMON_LINK_FLAGS} -Wl,-Map=${EXECUTABLE_FILE_NAME}.map -Wl,--unresolved-symbols=ignore-all"
        )
add_custom_command(TARGET ${EXECUTABLE_NAME}
        POST_BUILD
        COMMAND ${CMAKE_NM} --undefined-only ${EXECUTABLE_FILE_NAME}.out | sed -e 's/.* U \\\(.*\\\)/EXTERN\(\\1\);/' > "${EXECUTABLE_FILE_NAME}.syms"
        COMMENT "post build steps for ${EXECUTABLE_FILE_NAME}")

set(EXECUTABLE_NAME ${APP_REAL})
set(EXECUTABLE_FILE_NAME ${EXECUTABLE_NAME})
set(SYMBOL_DEF_FILE "${CMAKE_BINARY_DIR}/src/base/dynamic_code-base.syms")
add_dependencies(${EXECUTABLE_NAME} dynamic_code-base)
set_target_properties(${EXECUTABLE_NAME} PROPERTIES
        SUFFIX ".out"
        LINK_DEPENDS "${SYMBOL_DEF_FILE}"
        LINK_FLAGS "${COMMON_LINK_FLAGS} -Wl,-Map=${EXECUTABLE_FILE_NAME}.map -Wl,-R${SYMBOL_DEF_FILE}"
        )
add_custom_command(TARGET ${EXECUTABLE_NAME}
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} --change-addresses 0x30000 ${EXECUTABLE_FILE_NAME}.out "${EXECUTABLE_FILE_NAME}.out"
        #todo: following line only for testing
        COMMAND ${CMAKE_OBJDUMP} -d "${CMAKE_BINARY_DIR}/src/app/CMakeFiles/dynamic_code-app.dir/main.cpp.o" > "main.asm"
        COMMAND ${CMAKE_SIZE_UTIL} ${EXECUTABLE_FILE_NAME}.out
        COMMAND ${CMAKE_OBJDUMP} -d ${EXECUTABLE_FILE_NAME}.out > "${EXECUTABLE_FILE_NAME}.asm"
        COMMAND ${CMAKE_OBJCOPY} -O binary ${EXECUTABLE_FILE_NAME}.out "${EXECUTABLE_FILE_NAME}.bin"
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${EXECUTABLE_FILE_NAME}.out "${EXECUTABLE_FILE_NAME}.hex"
        COMMAND ${CMAKE_NM} ${EXECUTABLE_FILE_NAME}.out | sed -e 's/\\\([0-9a-f]*\\\) . \\\(.*\\\)/\\2 = 0x\\1;/' > "${EXECUTABLE_FILE_NAME}.syms"
        COMMENT "post build steps for ${EXECUTABLE_FILE_NAME}")
