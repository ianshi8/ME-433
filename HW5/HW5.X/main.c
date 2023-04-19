#include "nu32dip.h"
#include "spi.h"
#include <math.h>

unsigned short make_byte(unsigned char a_or_b, unsigned short volt);

int main() {
    NU32DIP_Startup();
    initSPI();
    // values for triangle wave
    int sign = 1;
    int j = 0;
    while(1) {
        // figure out voltage for sine wave, v = A*sine(2*pi*t/sample_rate)+B
        // math to make sinewave 0 to 1023
        int i = 0;
        for (i = 0; i < 628; ++i) {
            _CP0_SET_COUNT(0);
            // make 2Hz sin wave
            unsigned short v_sin = 500*sin(6.28*i/100.0) + 511.5; // scaled a little bit so ends don't clip
            unsigned short p_sin = make_byte(0, v_sin);
            // send sin wave voltage for spi
            LATBbits.LATB6 = 0;
            spi_io(p_sin>>8);
            spi_io(p_sin);
            LATBbits.LATB6 = 1;         
            // make 1Hz triangle wave
            unsigned short v_tri = (short) j*(1000.0/628.0); // scaled a little bit so ends don't behave odd
            if (sign == 1) {
                ++j;
            }
            else {
                --j;
            }
            unsigned short p_tri = make_byte(1, v_tri);
            LATBbits.LATB6 = 0;
            spi_io(p_tri>>8);
            spi_io(p_tri);
            LATBbits.LATB6 = 1;  
            
            // delay 5ms
            while (_CP0_GET_COUNT() < 240000) {       
            }
        }
        sign = sign*-1;
    }
}

unsigned char make_byte(unsigned char a_or_b, unsigned short volt) {
    // [a_or_b 1 1 1 [10 bit volt] 0 0]
    unsigned short output = 0b0000000000000000;
    output = 0b111<<12;
    output = output|(a_or_b<<15);
    output = output|(volt<<2);
    return output;
}