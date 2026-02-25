#include<reg51.h>

void delay(unsigned char count){
	unsigned int i,j;
	for(i=0;i<count;i++){
		for(j=0;j<=1275;j++){}
		}
	}

void main(){
	while(1){
		unsigned int i;
		for(i=0;i<=256;i++){
			P1=i;
			delay(10);
		}
	}
}