#include "nu32dip.h" // constants, functions for startup and UART

void delay(void);
int get_degree(int degree);

int main(void) {
    NU32DIP_Startup();
    
    T2CONbits.TCKPS = 4;     // Timer2 prescaler N=16
    PR2 = 59999;              // period = (PR2+1) * N * (1/48000000) = 50 Hz
    TMR2 = 0;                // initial TMR2 count is 0
    RPB15Rbits.RPB15R = 0b0101; // setting RPB15 pin to OC1
    OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
    OC1CONbits.OCTSEL = 0;   // Use timer2
    OC1RS = 3225;             // duty cycle 1800-7500 is ~180 deg range
    OC1R = 3225;              // initialize before turning OC1 on; afterward it is read-only
    T2CONbits.ON = 1;        // turn on Timer2
    OC1CONbits.ON = 1;       // turn on OC1
    
    while(1) {
        delay();
        OC1RS = 6075;
        delay();
        OC1RS = 3225;
    }
}

void delay(void){
    float time = 4;
    float clocks= time/(1.0/24000000.0);
   
    _CP0_SET_COUNT(0);
    while(_CP0_GET_COUNT() < clocks){}
}

int get_degree(int degree) {
    int min = 1800;
    int max = 7500;
    int duty_cycle = 1800+ (degree/180)*(max-min);
    return duty_cycle;
}