#include "nu32dip.h" // constants, functions for startup and UART
#include "i2c_master_noint.h"
#include "mpu6050.h"
#include "ssd1306.h"
#include <stdio.h>

void delay(void);
void blink(int, int); // blink the LEDs function

int main(void) {
    NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
    init_mpu6050();
    ssd1306_setup();
       
    unsigned char data[14];
    char accel[50];
    char fps_arr[50];
    float az;
    float time;
    float fps;
    
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
        _CP0_SET_COUNT(0);
        burst_read_mpu6050(data);
		// convert data
        az = conv_zXL(data);
        sprintf(accel, "Z acc: %.2f", az);
        drawString(accel, 5, 5);
        ssd1306_update();
        time = _CP0_GET_COUNT();
        time = time/48000000;
        fps = 1/time;
        sprintf(fps_arr, "FPS: %f", fps);
        drawString(fps_arr, 5, 15);
        ssd1306_update();  
    }
}


void delay(void) {
    _CP0_SET_COUNT(0);
    while (_CP0_GET_COUNT() < 24000*200) {
    }
}
