
/*

    Author: Erika Alves.
    Date: 25/08/2023.

    Main.cpp constains an use example of WS281B module.

*/

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