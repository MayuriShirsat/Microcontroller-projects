#include<reg51.h>

sbit LED1=P2^0;
sbit LED2=P2^1;
sbit BUTTON=P2^2;

void delay(unsigned int count){
	unsigned int i,j;
	for(i=0;i<count;i++){
		for(j=0;j<=1275;j++){}
		}
	}
	
void pattern1(){
	LED1=1;LED2=0;
	delay(500);
	LED1=0;LED2=1;
	delay(500);
}
void pattern2(){
	LED1=1;LED2=1;
	delay(200);
	LED1=0;LED2=0;	
	delay(300);
	LED1=1;LED2=1;
	delay(200);
	LED1=0;LED2=0;	
}
void main(){
  unsigned char mode = 0;   // 0 = pattern1, 1 = pattern2	
	BUTTON=1;//input

	while(1){
     if(BUTTON == 0){         // if button pressed
         delay(200);          // debounce
         if(BUTTON == 0){     // still pressed
             mode = !mode;    // toggle mode
             while(BUTTON==0); // wait for release
         }
     }
/*If button is pressed (BUTTON==0)  wait a little (delay(200)) to remove switch bounce.
Check again if button is still pressed. If yes  we treat this as a valid press.
mode = !mode;  toggles mode:
If mode was 0, it becomes 1.
If mode was 1, it becomes 0.
while(BUTTON==0);  wait here until the button is released.
(So one press counts only once).
If mode==0  run pattern1() (alternate blinking).
If mode==1  run pattern2() (both blink together).		 
*/
     if(mode == 0)
         pattern1();
     else
         pattern2();
	}
}
 