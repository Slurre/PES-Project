#include "boards.h"
#include "nrf_delay.h"
#include <stdlib.h>
#include <string.h>

typedef int (*app_func)(void);

typedef struct __attribute__((__packed__)) {
    uint32_t size_got, size_data, size_bss, size_text;
} app_header_t;

// taken from nRF5 SDK blinky example
int main(void) {

    /* Configure board. */
    bsp_board_init(BSP_INIT_LEDS);

    // debug phase 1: blink LED2
    bsp_board_led_on(2); nrf_delay_ms(500);
    bsp_board_led_off(2); nrf_delay_ms(500);

    uint8_t *addr = (uint8_t *)0x30000;
    app_header_t *header = (app_header_t *)addr;

    const uint32_t size_header = sizeof(app_header_t);

    uint8_t *payload = addr + size_header;
    uint32_t *file_got = (uint32_t *)payload;
    uint8_t *file_data = payload + header->size_got;
    // bss is not actually stored in FILE, since it only contains zeros
    uint8_t *file_text = payload + header->size_got + header->size_data;

    // debug phase 1: blink LED3
    bsp_board_led_on(3); nrf_delay_ms(500);
    bsp_board_led_off(3); nrf_delay_ms(500);

    uint32_t ram_size = header->size_got+header->size_data+header->size_bss;
    void *ram_buffer = malloc(ram_size);
    if (ram_buffer == NULL) {
        // debug phase 1b > malloc unsuccessful: blink LED0 forever
        while (true) { bsp_board_led_invert(0); nrf_delay_ms(500); }
    }

    // copy and initialize GOT
    uint32_t ram_offset = (uint32_t)ram_buffer + header->size_got;
    uint32_t *ram_got = (uint32_t *)ram_buffer;
    uint8_t *ram_data = ram_buffer + header->size_got;
    uint8_t *ram_bss = ram_buffer + header->size_got + header->size_data;
    for (uint32_t i=0; i<header->size_got/4; i++) {
        ram_got[i] = ram_offset + file_got[i];
    }

    // debug phase 1: blink LED3
    bsp_board_led_on(3); nrf_delay_ms(500);
    bsp_board_led_off(3); nrf_delay_ms(500);

    // copy .data
    memcpy(ram_data, file_data, header->size_data);
    // initialize .bss
    memset(ram_bss, 0, header->size_bss);

    app_func app_start = (app_func)(file_text + 1); // thumb bit!

    // debug phase 2: blink LED1
    bsp_board_led_on(1); nrf_delay_ms(500);
    bsp_board_led_off(1); nrf_delay_ms(500);

    /* Call app every 500ms. */
    while (true)
    {
        // store pointer to GOT table in register r9 (expected by app)
        __asm__ __volatile__("ldr r9, %[mem]" :: [mem] "m" (ram_got));
        app_start();
        nrf_delay_ms(500);
    }
}
