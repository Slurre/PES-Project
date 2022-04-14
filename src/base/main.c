#include "boards.h"
#include "nrf_delay.h"
#include "dynamic_app.h"

// taken from nRF5 SDK blinky example
int main(void) {

    app_func app_main = (app_func)0x30001; // address defined in app.ld + 1 ("thumb bit")

    // move app
    relocate_app(&app_main, (void*)0x40000);

    /* Configure board. */
    bsp_board_init(BSP_INIT_LEDS);

    /* Toggle LED0. */
    while (true)
    {
        bsp_board_led_invert(0);
        app_main();
        nrf_delay_ms(500);
    }
}

