# **WS2812B Module**

Basically you first need to create a instance of the `WS2812B_module` Classe, and pass by parameter the `GPIO_PIN` and `NUM_LEDS`, if no `GPIO_PIN` is set, by default it is GPIO 0.
Next you need to set each pixel led value using `set_value()` function, and to send all information to module use `show()` function. More details can be seen on `main.cpp`

```
#include <iostream>
#include <pico/stdlib.h>

#include "src/WS2812B.h"

#define RGB_PIN 0       // GPIO 0
#define NUM_PIXELS 8    // Number of pixels

int main() {
    
    // Init all inputs and outputs
    stdio_init_all();

    // WS2812B
    WS2812B_Module *RGB = new WS2812B_Module(RGB_PIN, NUM_PIXELS);

    while(1){    

        // Simple example

        // Set leds
        RGB->set_value(7, 100, 100, 100);

        RGB->set_value(1, 0, 255, 0);
        RGB->set_value(2, 255, 0, 0);
        RGB->set_value(3, 0, 0, 255);

        RGB->set_value(4, 255, 255, 0);
        RGB->set_value(5, 0, 255, 255);     // same as 0x00ffff
        RGB->set_value(6, 255, 0, 255);

        RGB->set_value(0, 0xffffff);        // same as (255, 255, 255)

        // Show all
        RGB->show();

        sleep_ms(600);
        
    }

    return 0;
}
```

## **To Implement**
* **Implement Nanoseconds Sleep function using systick from RP2040.** Currently, to have an action similar to a nanosecond sleep to implement the protocol mentioned in the WS2812B [manual], the assembly's "NOP" operation is used.

## **Build**
Inside `/WS2812B_Module` directory execute the next steps:
```
mkdir build
cd build
cmake ..
make
```
If your are using Windows, please use `cmake -G "MinGW Makefiles" ..` instead of `cmake ..`

## **Uploading file**
To upload the file inside the PI PICO, first plug it in bootloader mode, and drag the `.uf2` to the directory that popped when you plugged the pi pico on bootloader mode.
The `.uf2` file can be found inside `/build` directory.

[manual]: https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf
