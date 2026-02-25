// digit	dp(dot)	G	F	E	D	C	B	A		hex value
//   0			0			0	1	1	1	1	1	1			0x3f
//	 1			0			0	0	0	0	1	1	0     0x06
//similarly		0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67 

#include<reg51.h>

void delay(unsigned int count){
	unsigned int i,j;
	for(i=0;i<count;i++){
		for(j=0;j<1275;j++){}
		}
	}
unsigned char arr[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
// For common cathode: 0–9 and from g(MSB) to a(LSB) with h=0
// For common cathode: 0–9 and from a(LSB) to g(MSB) with h=0 -> 0xfc,0x60,0xDA,.....};

void main(){
	unsigned int i;
	while(1){
	for(i=0;i<10;i++){
		P2 = arr[i];
		delay(500);}
	}
}
//for common Anode: 0-9 and from g(MSB) to a(LSB) with h=1  ->	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
//for common Anode: 0-9 and from a(LSB) to g(MSB)  with h=1  ->	0x03,0x9f,0x25,......};