#include<reg51.h>

unsigned char arr[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
//arr[] Lookup table is for LED 
void delay(unsigned int count){
	unsigned int i;
	while(count){
		i=115;
		while(i>0){
			i--;
			count--;
		}
	}
}
	void main(){
		unsigned char ch = 0;
		while(1){
			P2 = arr[ch];//for ch=0 0x3F(0011 1111) ie 0 is on led at P2 port 
			delay(500);
			ch++;
			if(ch>9)
				ch=0;}
			}
			