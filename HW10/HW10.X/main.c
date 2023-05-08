#include "nu32dip.h" // constants, functions for startup and UART
#include "ws2812b.h"

void delay(void);

int main(void) {
    NU32DIP_Startup();
    ws2812b_setup();
    
    // setting hues
    float hue1 = 0;
    float hue2 = 72;
    float hue3 = 144;
    float hue4 = 216;
    float hue5 = 288;
    
    float b1 = 0.1;
    float b2 = 0.3; 
    float b3 = 0.5; 
    float b4 = 0.7;
    float b5 = 0.9;
    
    float i1=  0.0011;
    float i2=  0.0014;
    float i3=  0.0013;
    float i4=  0.0012;
    float i5=  0.00123;

    while(1){ 
        
        wsColor col1 = HSBtoRGB(hue1, 0.8, b1);
        wsColor col2 = HSBtoRGB(hue2, 0.8, b2);
        wsColor col3 = HSBtoRGB(hue3, 0.8, b3);
        wsColor col4 = HSBtoRGB(hue4, 0.8, b4);
        wsColor col5 = HSBtoRGB(hue5, 0.8, b5);
        
        wsColor cols[5] = {col1, col2, col3, col4, col5};
        
        b1=b1+i1;
        b2=b2+i2;
        b3=b3+i3;
        b4=b4+i4;
        b5=b5+i5;
        
        if(b1>0.999 || b1<0){
            i1 = -i1;
        }
        if(b2>0.999 || b2<0){
            i2 = -i2;
        }
           if(b3>0.999 || b3<0){
            i3 = -i3;
        }
         if(b4>0.999 || b4<0){
            i4 = -i4;
        }
        if(b5>0.999 || b5<0){
            i5 = -i5;
        }
        
        ws2812b_setColor(cols, 5); 
        
        
    }    
}


void delay(void){
    float time = 0.05;
    float clocks= time/(1.0/24000000.0);
   
    _CP0_SET_COUNT(0);
    while(_CP0_GET_COUNT() < clocks){}
}