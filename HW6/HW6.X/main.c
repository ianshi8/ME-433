#include "nu32dip.h"
#include "i2c_master_noint.h"

void delay(void);
void i2c_write(unsigned char add, unsigned char reg, unsigned char val);
unsigned char i2c_read(unsigned char w_add, unsigned char r_add, unsigned char reg);

int main() {
    NU32DIP_Startup();
    i2c_master_setup();
    i2c_write(0b01000000,0x00,0b0111111); //set IODIRA
    while (1) {
        // heartbeat yellow LED
        LATBINV = 0b100000;
        delay();
        if(i2c_read(0b01000000, 0b01000001, 0x09) == 1) {
            i2c_write(0b01000000, 0x0A, 0b10000000);
        }
        else {
            i2c_write(0b01000000, 0x0A, 0b00000000);
        }
        
    }
    
}

void delay(void) {
    _CP0_SET_COUNT(0);
    while (_CP0_GET_COUNT() < 24000*200) {
    }
}

void i2c_write(unsigned char add, unsigned char reg, unsigned char val) {
    i2c_master_start();
    i2c_master_send(add);
    i2c_master_send(reg);
    i2c_master_send(val);
    i2c_master_stop();
}

unsigned char i2c_read(unsigned char w_add, unsigned char r_add, unsigned char reg) {
    i2c_master_start();
    i2c_master_send(w_add);
    i2c_master_send(reg);
    i2c_master_restart();
    i2c_master_send(r_add);
    unsigned char r = i2c_master_recv();
    i2c_master_ack(1);
    i2c_master_stop();
    return (r&0b1);
}