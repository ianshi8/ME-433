#include "nu32dip.h" // constants, functions for startup and UART
#include "i2c_master_noint.h"
#include "mpu6050.h"
#include <stdio.h>

void blink(int, int); // blink the LEDs function

int main(void) {
    NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
    init_mpu6050();
	
	// char array for the raw data
    unsigned char data[14]; 
	// floats to store the data
    float ax, ay, az, gx, gy, gz, temp;
	
	// read whoami
    unsigned char who;
    who = whoami();
    
	// print whoami
    char message[100];
    sprintf(message, "0x%X\r\n", who);
    NU32DIP_WriteUART1(message);
	// if whoami is not 0x68, stuck in loop with LEDs on
	// wait to print until you get a newline
    NU32DIP_ReadUART1(message,100);

    while (1) {
		// use core timer for exactly 100Hz loop
        _CP0_SET_COUNT(0);
        blink(1, 5);

        // read IMU
        burst_read_mpu6050(data);
		// convert data
        ax = conv_xXL(data);
        ay = conv_yXL(data);
        az = conv_zXL(data);
        gx = conv_xG(data);
        gy = conv_yG(data);
        gz = conv_zG(data);
        temp = conv_temp(data);

        // print out the data
        sprintf(message, "%f\r\n", ax);
        NU32DIP_WriteUART1(message);

        while (_CP0_GET_COUNT() < 48000000 / 2 / 100) {
        }
    }
}

// blink the LEDs
void blink(int iterations, int time_ms) {
    int i;
    unsigned int t;
    for (i = 0; i < iterations; i++) {
        NU32DIP_GREEN = 0; // on
        NU32DIP_YELLOW = 1; // off
        t = _CP0_GET_COUNT(); // should really check for overflow here
        // the core timer ticks at half the SYSCLK, so 24000000 times per second
        // so each millisecond is 24000 ticks
        // wait half in each delay
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }

        NU32DIP_GREEN = 1; // off
        NU32DIP_YELLOW = 0; // on
        t = _CP0_GET_COUNT(); // should really check for overflow here
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }
    }
}

