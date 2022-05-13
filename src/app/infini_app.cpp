#include "infini_app.h"
#include "boards.h"
#include <stdint.h>

Leds::Leds() {
  this->running = 1;
}

void Leds::blink_leds(void) {
    /* Toggle all LEDs. */
    for (uint8_t i=0; i<4; i++)
        bsp_board_led_invert(i);
}

void Leds::blink_led(uint8_t led_nr) {
  bsp_board_led_invert(led_nr);
}

void Leds::blink_leds_vector(MyVector<uint8_t> led_nrs) {
  for (uint8_t i = 0; i < led_nrs.size_of(); i++) {
    if (led_nrs.get(i) == 1) {
      bsp_board_led_invert(i);
    }
  }
}
