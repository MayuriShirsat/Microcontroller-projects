/*
1.first address lines are given to select the i/p channel
2.ALE is enable(0->1->0) (to latch the address)
3.SOC is enable(0->1->0) to start the conversion
4.continously check the EOC 
5.if EOC(1->0) OE is enable(0->1) (to make data avaliable on port)
6.stop*/
#include<reg51.h>

sbit X=P2^0;
sbit Y=P2^1;
sbit Z=P2^2;
sbit SOC=P2^3;
sbit ALE=P2^4;
sbit OE=P2^5;
sbit EOC=P2^6;

unsigned char adc_data;

void delay(unsigned int ms) {
    unsigned int i, j;
    for(i=0; i<ms; i++)
        for(j=0; j<1275; j++);
}

unsigned char start(unsigned char channel){ 
  X = channel & 0x01;
	Y = (channel >> 1) & 0x01;
  Z = (channel >> 2) & 0x01;
/*Say channel = 5 ? binary = 101  
->we know 'x & 1 = x'
X = 5(101) & 001 = 1 -> A=1
Y = (5>>1)(010) & 001 = 0 -> B=0
Z = (5>>2)(001) & 001 = 1 -> C=1	*/
	ALE=1;
	delay(1);
	ALE=0;
	SOC=1;
	delay(1);	
	SOC=0;
	
while(EOC==1);
//the semicolon after while(EOC==1); this means “do nothing while EOC is high”.
// do not use if loop  
// If you use if(EOC == 1) you only check once.
// while(EOC == 1) keeps CPU stuck here until conversion is done	
// wait while EOC is high
// Now EOC=0 ? conversion finished 
    OE=1;
	  adc_data=P1;
		OE=0;
		return adc_data;
	}

void main(){  
	
	  while(1){
			  unsigned char _data = start(0);
	      delay(100);
	}
}
