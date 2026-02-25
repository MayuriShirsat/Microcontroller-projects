#include <reg51.h>
#include <intrins.h>   // for _crol_ (rotate left)

sbit led = P2^0;   

void delay(unsigned int count){
	unsigned int i,j;
	for(i=0;i<=count;i++){
		for(j=0;j<=1275;j++){}
		}
	}

void main() {
	unsigned char x = 0x01;
    TMOD = 0x05;   
	  TH0 = 0x00;    // Clear counter each time counting start from 0 to 10
    TL0 = 0x00;
    TR0 = 1;       // Start Counter
    
    while (1) {
			  unsigned int i;
        if (TL0 >= 10) { 					// If 10 pulses received on T0 pin (P3.4)
					for(i=0;i<=7;i++){
          P2 = x;
          delay(300);
						x = _crol_(x,1);//rotate LED to next position
          }						
            TH0 = 0x00;    // Reset counter
            TL0 = 0x00;
        }
    }
}
//without _crol_ fun (circular rotate left)
//x = x << 1;    // shift left
//if(x == 0x00)  // if all LEDs went off
//x = 0x01;  // restart from first LED