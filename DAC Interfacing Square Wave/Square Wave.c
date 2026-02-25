#include<reg52.h>

void delay(){
	TMOD=0X01;
	TH0=0xF7;
	TL0=0x00;
	TR0=1;
	while(TF0==0);
	  TR0=0;
		TF0=0;
}

void main(){
	
	while(1){
		P1=0x00;//First 2.5 ms -> P1 low.
		delay();
		P1=0xFF;//Next 2.5 ms -> P1 high.
		delay();
	}
}
//P1 port is connected to DAC and at o/p we get square wave
		
/*Quick math (11.0592 MHz crystal)
Desired frequency = 200 Hz -> period T = 1/200 = 5 ms.
Half-period (toggle interval) = 2.5 ms.
8051 machine cycle = 12 oscillator clocks -> 1 / (11.0592 MHz / 12) = 1.085 µs per tick.
Required ticks = 2.5 ms / 1.085 µs = 2304 ticks exactly.
For a 16-bit timer (mode 1) the timer counts from initial value up to 0xFFFF. So initial value = 65536 - 2304 = 63232 = 0xF700.


OUTPUT CALCULATION OF DAC ->

Iout=Iref·(b7/2+b6/4+b5/8+b4/16+b3/32+b2/64+b1/128+b0/256)

Vout==Rf·Iout
*/