#include<reg51.h>
sbit led = P3^0;
sbit sw = P3^7;
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
		sw = 1;	//input pin
		while(1){
			if (sw == 0){
				led = 1;
				delay(1000);
				led = 0;
			}
			else{
				led = 0;}
			}
		}
	//pull-up and pull-down are used for switch