#include <reg51.h>

void uart_init() {                              //SM0 SM1 SM2 REN TB8 RB8 TI RI
    SCON = 0x50;    // Mode 1, 8-bit UART-> 0x50 = 0   1   0   1   0   0   0  0
    TMOD = 0x20;    // Timer1 mode2(Always use mode 2 for baud rate) (8-bit auto reload)
    TH1 = 0xFD;     // Baud rate 9600
    TL1 = 0xFD;
    TR1 = 1;        // Start Timer1
    TI = 1;         // Set TI to indicate ready to transmit
}
/*BAUD RATE->
9600	0xFD	253	Most common
4800	0xFA	250	Half of 9600
2400	0xF4	244	Half of 4800
1200	0xE8	232	Half of 2400
19200	0xFE	254	Fast serial communication*/
void main() {
    uart_init();
    while(1) {
        SBUF = 'A';        // Send character on inbuilt SBUF
        while(TI == 0);    // Wait for transmission complete
        TI = 0;            // Clear transmit flag
    }
}

/*Baud Rate=2^SMOD*Oscillator Frequency/32×12×(256-TH1)
Where:
SMOD = 0 or 1 (bit in PCON register, 0 -> default)
Oscillator Frequency = crystal frequency, e.g., 11.0592 MHz
TH1 = reload value for Timer1
Note: TL1 is ignored in auto-reload mode; TH1 is the main reload value.*/	