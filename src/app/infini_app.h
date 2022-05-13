#include <stdint.h>
#include <vector>

template <class T> class MyVector {
public:
  MyVector(uint8_t* const v, uint8_t const v_size) : value {v}, size {v_size} {
  } // Use MIL and const-lvalue-ref

  void push_back(T const val) {
    this->value[this->count] = val;
    this->count++;
  }

  T get(uint8_t const index) {
    if (index <= this->size)
      return this->value[index];
    return (T)0;
  }

  uint8_t size_of() {
    return this->size;;
  }

private:
  T* value {};  // NSDMI - default initialise type
  uint8_t size {};
  uint8_t count = 0;
};

class Leds {
public:
  Leds();
  void blink_leds();
  void blink_led(uint8_t led);
  void blink_leds_vector(MyVector<uint8_t> led_nrs);
  //void blink_leds_array(uint8_t* led_nrs);
private:
  int running = 0;
};

/*
* - Giving args to app for function from base
* - Find most likely types (also std libs) that are used throughout infinitime
* - Use more functions: DONE
*/
