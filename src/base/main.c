#include "boards.h"
#include "nrf_delay.h"
#include "dynamic_app.h"

// taken from nRF5 SDK blinky example
int main(void) {

    app_func app_main = (app_func)0x30101; // address defined in app.ld + 1 ("thumb bit")

    init_flash();

    // move app and wait for completion
    relocate_app();

    init_flash();
    
    // move app
    relocate_app(&app_main, (void*)0x30010);
  

    /* Configure board. */
    bsp_board_init(BSP_INIT_LEDS);

    /* Call app every 500ms. */
    while (true)
    {
<<<<<<< HEAD
        app_main();
=======
        bsp_board_led_invert(0);
        //app_main();
>>>>>>> fbb8d7c4ed3311138e806e97dbe66196970bc9dc
        nrf_delay_ms(500);
    }
}

