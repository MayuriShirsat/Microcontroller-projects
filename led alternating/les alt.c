#include<reg51.h>

void delay(unsigned int count){
unsigned int i,j;
for(i=0;i<=count;i++){
for(j=0;j<1275;j++){}
}
}
void main(){
	while(1){
		P3 = 0xAA;	//1010 1010(AA)  to 0101 0101(55)
		delay(1000);
		P3 = 0x55;
		delay(1000);
	}
		}