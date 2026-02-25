#include <reg51.h>
sbit red = P2^0;
sbit green = P2^1;
sbit yellow = P2^2;

void delay(unsigned int count){
		unsigned int i,j;
		for(i=0;i<count;i++){
			for(j=0;j<=1275;j++){}
		}
}
	
void main(){
	unsigned char arr[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
	unsigned int i;
			
while(1){	
	red = 1;
	for(i=0;i<10;i++){
		P1 = arr[i];
		delay(1000);
	}		
	red=0;
				
	green = 1;
	for(i=0;i<10;i++){
		P1 = arr[i];
		delay(1000);
	}
	green= 0;
				
	yellow = 1;
	delay(5000);
	yellow = 0;
   }
}
