#include<reg51.h>

void delay(void){
	TMOD=0x01; //timer 0 mode 1
	TH0=0x4B;
	TL0=0xFE;
	TR0=1;
	while(TF0==0);
		TR0=0;
		TF0=0;
	}
	void main(void){
		while(1){
		P2=0x55;
		delay();
		P2=0xAA;
		delay();}
	}