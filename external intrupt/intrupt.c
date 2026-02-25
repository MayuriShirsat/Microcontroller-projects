#include <reg51.h>
#include <stdio.h>

sbit RS = P3^1;
sbit EN = P3^2;
sbit led = P3^0;

void delay_ms(unsigned int ms);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char dat);
void lcd_init();
void lcd_string(char *str);

void main() {
    unsigned int sec = 0;
	char buffer[16];//to store the sec in integer form as LCD can not read integers (except:"1","0")

    lcd_init();//call

    lcd_string("  Welcome !!!  ");
    delay_ms(2000);      
    lcd_cmd(0x01);       // Clear screen
    lcd_string("Counting Secs:");
    EA = 1;
	  EX0 = 1;
	  IT0 = 1;
    while(1) {
        lcd_cmd(0xC0);   // Move to 2nd line
			sprintf(buffer, "Sec: %u   ", sec);//hold sce value as "Sec:5" etc
        lcd_string(buffer);//pass to string to display
        sec++;
        delay_ms(1000);  // 1 second delay
    }
}
void delay_ms(unsigned int ms) {
    unsigned int i,j;
    for(i=0;i<ms;i++)
        for(j=0;j<1275;j++);  
}
void lcd_cmd(unsigned char cmd) {
    P2 = cmd;
    RS = 0;
    EN = 1;
    delay_ms(2);
    EN = 0;
}
void lcd_data(unsigned char da) {
    P2 = da;
    RS = 1;
    EN = 1;
    delay_ms(2);
    EN = 0;
}
void lcd_init() {		//command og LCD
    lcd_cmd(0x38);  
    lcd_cmd(0x0C);  
    lcd_cmd(0x06);  
    lcd_cmd(0x01);  
    delay_ms(2);
}

void lcd_string(char *str) {
    while(*str != '\0') {
        lcd_data(*str++);
    }
}
void ISR_ex0(void) interrupt 0 //external interrupt
{
	led = ~led;
	//never use delay here in interrupt fun
}