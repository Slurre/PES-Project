#include "boards.h"
#include "nrf_delay.h"
#include "app.h"
#include "infini_app.h"
#include <vector>
#include <stdint.h>

// void blink_led(void) {
//     /* Toggle LED1. */
//     bsp_board_led_invert(1);
// }
//
// void blink_leds(void) {
//     /* Toggle all LEDs. */
//     for (uint8_t i=0; i<4; i++)
//         bsp_board_led_invert(i);
// }

int app_main(void) {
    Leds app;

    /* Test naked function call: */
    //app.blink_leds();

    /* Test by giving parameter: */
    //app.blink_led(3);

    /* Test using vectors: */
    uint8_t nr_of_leds[4];
    MyVector<uint8_t> leds_to_blink(&nr_of_leds[0], 4);
    leds_to_blink.push_back(0);
    leds_to_blink.push_back(1);
    leds_to_blink.push_back(0);
    leds_to_blink.push_back(1);
    app.blink_leds_vector(leds_to_blink);

    return 0;
}
