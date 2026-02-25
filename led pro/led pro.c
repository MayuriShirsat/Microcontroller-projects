#include<reg51.h>

void delay(unsigned int count){
while(count){
unsigned int i;
i=115;
while(i>0)
i--;
count--;
	}
}
void main(){
	
unsigned char i;
while(1)
{
for(i=0;i<10;i++){
P3 = 0xFF;
delay(500);
P3 =0x00;
delay(500);
}
	
delay(1000);
	
for(i=0;i<10;i++){
P3 = 0x55;
delay(500);
P3 = 0xAA;
delay(500);
}

delay(1000);
	}
}	