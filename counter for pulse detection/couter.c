#include <reg51.h>
sbit led = P2^0;   

void main() {
    TMOD = 0x05;   
	  TH0 = 0x00;    // Clear counter each time counting start from 0 to 10
    TL0 = 0x00;
    TR0 = 1;       // Start Counter
    
    while (1) {
        if (TL0 >= 10) {   // If 10 pulses received on T0 pin (P3.4)
            led = ~led;    
            TH0 = 0x00;    // Reset counter
            TL0 = 0x00;
        }
    }
}