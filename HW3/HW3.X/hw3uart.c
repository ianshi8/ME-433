#include "nu32dip.h" // constants, functions for startup and UART
#include <math.h>

int main(void) {
    char message[100];

    NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
    while (1) {
        int i = 0;
        if (!NU32DIP_USER) {
            for (i = 0; i < 100; ++i) {
                sprintf(message, "%f\r\n", 1.65*sin(6.28*i/100.0)+1.65);
                NU32DIP_WriteUART1(message);
                _CP0_SET_COUNT(0);
                while (_CP0_GET_COUNT() < 240000) {
                }
            }
        }
        sprintf(message, "%f\r\n", 1.65);
        NU32DIP_WriteUART1(message);
        _CP0_SET_COUNT(0);
        while (_CP0_GET_COUNT() < 240000) {
        }
    }
}


