#include<reg51.h>

sbit BUTTON=P1^0;

unsigned char arr[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
//arr[] Lookup table is for 7 segment 
void delay(unsigned int ch){
	unsigned int i,j;
	for(i=0;i<ch;i++){
		for(j=0;j<=1275;j++){}
		}
	}

	void main(){
		unsigned int count=0;
		unsigned char unit_part;
		unsigned int tens_part;
		BUTTON=1;
		
		while(1){
		if(BUTTON==0){
			delay(200);
			if(BUTTON==0){
				count++;
		    if(count>99){
				  count=0;}				
			}
			while(BUTTON==0);//wait until button is released.
			}
		unit_part=count%10;
		tens_part=count/10;
			
		P3=arr[tens_part];
		P2=arr[unit_part];	
		}	
	}	
			
/*So, to simulate a button press, you need some input component in Proteus, for example:
Push button (switch)
Virtual keyboard (like “Logic Keyboard” or “Keypad” component in Proteus)*/