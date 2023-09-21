#include "WS2812B.h"

/*
    Constructors.
*/

WS2812B_Module::WS2812B_Module(uint16_t num_pixels) : RGB_PIN(0), NUM_LEDS(num_pixels) {  

    // Initializing  
    std::cout << "[WS2812B_Module]: %5s Started module at gpio 0" <<  std::endl;

    // Setting pin
    gpio_init(RGB_PIN);
    gpio_set_dir(RGB_PIN, GPIO_OUT);

    // Allocating strap
    strap = new pixel_t{NUM_LEDS};

    // Clear all leds
    clear_all_leds();
    sleep_ms(100);
};

WS2812B_Module::WS2812B_Module(uint8_t gpio_pin, uint16_t num_pixels) : RGB_PIN(gpio_pin), NUM_LEDS(num_pixels) {

    // Initializing  
    std::cout << "[WS2812B_Module]: Started module at gpio " << unsigned(RGB_PIN) << "." << std::endl;

    // Setting pin
    gpio_init(RGB_PIN);
    gpio_set_dir(RGB_PIN, GPIO_OUT);

    // Allocating strap
    strap = new pixel_t[NUM_LEDS];

    // Clear all leds
    clear_all_leds();
    sleep_ms(100);
};

/*
    Destructors.
*/

WS2812B_Module::~WS2812B_Module(){
    delete [] strap;
}

/*
    Description: Set pin for the module.
    Input:
        - uint8_t gpio_pin: gpio number.
*/

void WS2812B_Module::set_gpio(uint8_t gpio_pin){
    RGB_PIN = gpio_pin;
};

/*
    Description: set the value of an especific pixel led. Can either use hexcode or separeted (Red, Green and Blue).
    Input:
        - uint8_t num_leds: number of leds.
*/

void WS2812B_Module::set_value(uint8_t index, uint8_t G, uint8_t R, uint8_t B){
    
    // Setting values
    strap[index].red = R;
    strap[index].green = G;
    strap[index].blue = B;

};

void WS2812B_Module::set_value(uint8_t index, uint32_t hexcode){

    /*
        Input in RGB format
    */

    // Decompose input
    uint8_t R = hexcode & 0xff;
    uint8_t G = (hexcode >> 8) & 0xff; 
    uint8_t B = (hexcode >> 16) & 0xff;

    // Setting values
    strap[index].red = R;
    strap[index].green = G;
    strap[index].blue = B;

};

/*
    Description: Send one byte of information to the module.
    Input:
        - uint8_t value: byte to be sent.
*/

void WS2812B_Module::send_byte(uint8_t value){

    // Using bitmasking to read each bit from byte.
    uint8_t bit;

    // Iterating over each bit
    for(int i = 7; i >= 0; i--){

        // Getting bit
        bit = value & (1 << i);

        // Sending each bit
        if(bit >= 1){
            gpio_put(0, 1);
            sleep_900ns();    
            gpio_put(0, 0);
            sleep_350ns();
        } else if(bit == 0){
            gpio_put(0, 1);
            sleep_350ns();    
            gpio_put(0, 0);
            sleep_900ns();
        }
    }
}

/*
    Description: send the information of the color to be outputed.
    Input:
        - uint8_t G: Green value.   Range between 0 --> 255, or 0 --> 0xff.
        - uint8_t R: Red value.     Range between 0 --> 255, or 0 --> 0xff.
        - uint8_t B: Blue value.    Range between 0 --> 255, or 0 --> 0xff.
*/

void WS2812B_Module::send_hexcode(uint8_t G, uint8_t R, uint8_t B){

    // G
    send_byte(G);
    // R
    send_byte(R);
    // B
    send_byte(B);

}

/*
    Description: Clear all Leds.
*/

void WS2812B_Module::clear_all_leds(void){

    std::cout << "[WS2812B_Module]: Clearing all leds." << std::endl;

    //  Clearing
    for(int i = 0; i < NUM_LEDS; i++){

        // Send 0x000000 or (0, 0, 0) to clear
        send_hexcode(0, 0, 0);
    }
}

/*
    Description: Set number of pixel to basic color (Red, Green or Blue)
    Inputs:
        - int num_pixels: number of pixels to be set. If no parameter is passed, will use default number of pixels. 
*/

void WS2812B_Module::red(uint16_t num_pixels /*= 0*/){

    // If no number of pixls where set
    if(!num_pixels){
        num_pixels = NUM_LEDS;
    }

    for(int i = 0; i < NUM_LEDS; i++){

        // Red
        if(i < num_pixels){
            // Setting to red
            set_value(i, 0, 255, 0);
        } else {
            // setting to blank
            set_value(i, 0, 0, 0);
        }
    }

    // Show - Send information
    show();
}

void WS2812B_Module::blue(uint16_t num_pixels /*= 0*/){

    // If no number of pixls where set
    if(!num_pixels){
        num_pixels = NUM_LEDS;
    }

    for(int i = 0; i < NUM_LEDS; i++){

        // Blue
        if(i < num_pixels){
            // Setting to blue
            set_value(i, 0, 0, 255);
        } else {
            // setting to blank
            set_value(i, 0, 0, 0);
        }
    }

    // Show - Send information
    show();
}

void WS2812B_Module::green(uint16_t num_pixels /*= 0*/){

    // If no number of pixls where set
    if(!num_pixels){
        num_pixels = NUM_LEDS;
    }

    for(int i = 0; i < NUM_LEDS; i++){

        // Green
        if(i < num_pixels){
            // Setting to green
            set_value(i, 255, 0, 0);
        } else {
            // setting to blank
            set_value(i, 0, 0, 0);
        }
    }

    // Show - Send information
    show();
}


/*
    Description: Show leds.

*/

void WS2812B_Module::show(void){

    // Iterate over pixel list
    for(int8_t pixel_idx = 0; pixel_idx < NUM_LEDS; pixel_idx++){

        //
        send_hexcode(strap[pixel_idx].green, strap[pixel_idx].red, strap[pixel_idx].blue);
    }
}

/*
    TODO: Improve nano second functions.
    TODO: Create a library just for this?
    Sleep in nano seconds.
*/

void WS2812B_Module::sleep_350ns(void){

    // 44 x 8ns ~= 350ns
    __asm volatile ("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

}

void WS2812B_Module::sleep_900ns(void){

    // 112 x 8ns ~= 900ns
    __asm volatile ("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
    __asm volatile ("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
    __asm volatile ("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

}

/*
    Sleep Nanoseconds
*/

void WS2812B_Module::sleep_ns(uint16_t delay){
    
    // Define
    

}