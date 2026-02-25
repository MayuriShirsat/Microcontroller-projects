#include <reg51.h>
sbit red    = P2^0;
sbit green  = P2^1;
sbit yellow = P2^2;

unsigned char seg[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void delay(unsigned int count){
    unsigned int i, j;
    for(i=0; i<count; i++){
        for(j=0; j<1275; j++);
    }
}

void display_number(unsigned char num){
    unsigned char tens = num / 10;
    unsigned char ones = num % 10;

    P1 = seg[tens];   // Tens digit on Display 1
    P3 = seg[ones];   // Ones digit on Display 2
}

void countdown(unsigned char sec){
    unsigned int i;//dont take unsigned char as it do not decrement and roll to 255 and loop do not stop 
    for(i=sec; i>=0; i--){
        display_number(i);
        delay(1000);   // 1 second delay
    }
}

void traffic_light() {
    red = 1; countdown(30); red = 0;
    green = 1; countdown(25); green = 0;
    yellow = 1; countdown(5); yellow = 0;
}

void main() {
    while(1){
        traffic_light();
    }
}
