#ifndef WS2812B_H_   /* Include guard */
#define WS2812B_H_

/* Import libraries */
#include <iostream>            // Base c++ librarie with its standads methods
#include <pico/stdlib.h>

/* Macros */
typedef unsigned char uint8_t;          // Range from 0 --> 255    (2 ** 8  - 1)
typedef unsigned short uint16_t;        // Range from 0 --> 65.535 (2 ** 16 - 1)
typedef unsigned long uint32_t;         // Range from 0 -->        (2 ** 32 - 1)

/* 
    Pixel struct: contains informations of each value color (red, green and blue). 
*/
typedef struct pixel {

    uint8_t red;
    uint8_t green;
    uint8_t blue;

} pixel_t;

/* Class for the WS2812B module */
class WS2812B_Module {

    /* Protected variables */
    protected:
        uint8_t RGB_PIN;        // Gpio raspberry pi pico
        uint16_t NUM_LEDS;       // Number of leds from strap

        // List containing all information of each pixel LED.
        pixel_t *strap;

        // Send low level information to module
        void send_byte(uint8_t value);
        void send_hexcode(uint8_t G, uint8_t R, uint8_t B);

    /*  Public Methods */
    public:

        /*
            Constructor.
                Input
                    - uint8_t num_pixels: Number of led pixels.
                    - uint8_t gpio_pin: GPIO to send information. By default is GPIO 0.
        */
        WS2812B_Module(uint16_t num_pixelss);
        WS2812B_Module(uint8_t gpio_pin, uint16_t num_pixels);

        /*
            Destructors.
        */
        ~WS2812B_Module();     
   
        /* Other Methods */

        // Setting variables
        void set_gpio(uint8_t gpio_pin);
        void set_value(uint8_t index, uint8_t G, uint8_t R, uint8_t B);
        void set_value(uint8_t index, uint32_t hexcode);

        // Clear
        void clear_all_leds(void);

        // Nano Sleep
        void sleep_350ns(void);
        void sleep_900ns(void);
        void sleep_ns(uint16_t delay); // TODO: implement.

        // Basic Colors
        void red(uint16_t num_pixels = 0);
        void green(uint16_t num_pixels = 0);
        void blue(uint16_t num_pixels = 0);  

        // Show all pixel leds colors
        void show(void);

};

#endif // WS2812B