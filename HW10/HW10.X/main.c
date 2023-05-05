#include "nu32dip.h" // constants, functions for startup and UART
#include "ws2812b.h"

void delay(void);

int main(void) {
    NU32DIP_Startup();
    ws2812b_setup();
    
    // setting hues
    int i=0; //red
    int j=20;
    int k=40;
    int l=60; // green
    int numLEDs = 4;
    wsColor c[numLEDs];
    while(1) {
        c[0]=HSBtoRGB(180,1,1);
        c[1]=HSBtoRGB(180,1,1);
        c[2]=HSBtoRGB(180,1,1);
        c[3]=HSBtoRGB(180,1,1);
        ws2812b_setColor(c, numLEDs);
        /*
        c[0]=HSBtoRGB(i,1,1);
        c[1]=HSBtoRGB(j,1,1);
        c[2]=HSBtoRGB(k,1,1);
        c[3]=HSBtoRGB(l,1,1);
        
        i++;
        j++;
        k++;
        l++;      
        if (i-360>0){
            i=0;
        }
        if(j-360>0){
            j=0;
        }
        if(k-360>0){
            k=0;
        }
        if(l-360>0){
            l=0;
        }
        ws2812b_setColor(c, numLEDs);
         */
    } 
}

void delay(void){
    float time = 0.05;
    float clocks= time/(1.0/24000000.0);
   
    _CP0_SET_COUNT(0);
    while(_CP0_GET_COUNT() < clocks){}
}