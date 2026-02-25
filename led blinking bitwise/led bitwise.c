#include<reg51.h>
sbit led1 = P2^0;

void delay(unsigned int count){
	unsigned int i,j;
	for(i=0;i<=count;i++){
	for(j=0;j<1275;j++){}
	}
}
void main(){
	P2 = 0x00;
while(1){
	led1=0;
	delay(1000);
	led1=1;
	delay(1000);}
}
//	while(count){
//		i=115;
//	while(i>0)
//		i--;
//	count--;}
