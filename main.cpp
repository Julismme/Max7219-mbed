/*
example of driving Max7219 by mbed.

JiuZhang Jiang
jiu@myself.com
2017.5.18
*/
#include "mbed.h"
#define LOW 0
#define HIGH 1



DigitalOut load(p12);
//will provide the load signal
SPI max72_spi(p11, NC, p13);
//so p11,p12,p13 are Din,CS,CLK respectively
char  number[10][3]{{0x1f,0x11,0x1f},{0x00,0x00,0x1f},{ 0x1d,0x15,0x17},{ 0x15,0x15,0x1f},{ 0x07,0x04,0x1f},{ 0x17,0x15,0x1d},{ 0x1f,0x15,0x1d},{ 0x01,0x01,0x1f},{ 0x1f,0x15,0x1f},{ 0x17,0x15,0x1f}};
// use an matrix to store the date of numbers

void write( int reg, int col){//base writing function
    load = LOW;            
    max72_spi.write(reg);  
    max72_spi.write(col);  
    load = HIGH;           
}

void write_number(int a){//last write function when it doesn't beat
    int data; 
    int l=a/10;
    int r=a%10;
    if (l>9){
        l=r=9;
    }
    for(int i = 0; i <= 2; i++) {
        data = number[l][i]+0x40; 
        write(i+1,data);
    }
    for(int i = 3;i <= 5; i++) {
        data = number[r][i-3]+0x40; 
        write(i+1,data);
    }
    for(int i = 6;i <= 7; i++) {
        data =0x40; 
        write(i+1,data);
    }
}

void setup_dot_matrix (){
    // initiation of the max 7219
    // SPI setup: 8 bits, mode 0
    max72_spi.format(8, 0);
    max72_spi.frequency(100000); //100khz
    for (int i=1; i<=8; e++) {    // empty registers, turn all LEDs off
        write(e,0);
    }
}

void clear(){
     for (int e=1; e<=8; e++) {    // empty registers, turn all LEDs off
        write(e,0);
    }
}

int main(){
    setup_dot_matrix ();      /* setup matric */
    while(1){
        for(int i=0;i<100;i++){
            write_number(i);
            wait(1);
        }
    }
}
