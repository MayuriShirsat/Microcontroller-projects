//INFORMATION ABOUT RELAY
//there is only one o/p of 5 V in 8051
//relay is used to turn on or off the AC (can be DC) high power components in single signal
//transister is used between them for turning on or off its current should be in such a way that Ibe <=10mA for this r should be 33 ohm to 1 K ohm
//the IC ULN2803 have 8 relays in it

//note : pulling->opposite to intrrupt i.e. the external message wait untill going on program finish 
//LCD CODE
#include<reg51.h>
sbit rs=P1^0;
sbit en=P1^1;

void delay(unsigned int count){
	unsigned int i,j;
	for(i=0;i<=count;i++){
		for(j=0;j<1275;j++){}
		}
	}
void lcd_data(unsigned char xyz){
	rs=1;//data is sending on data lines
	P2=xyz;
	en=1;
	delay(50);//enable should be on off through the program 
	en=0;
}
void lcd_comd(unsigned char xyz){
	rs=0;//comand is sending on data lines
	P2=xyz;
	en=1;
	delay(50);//enable should be on off through the program 
	en=0;
}
void main(){
	lcd_comd(0x38);//initialize
	lcd_comd(0x02);//return home
	lcd_comd(0x01);//clear display
	lcd_comd(0x0C);//Display On Cursor Off
	lcd_comd(0x06);
	lcd_comd(0x80);//address of location on row of lcd
//for 1st row=0x80
//for 2nd row=0xC0
//for middle of 1st row=0x85
//for middle of 2st row=0xC5	
//similarly we can use 0x87,0xC3 etc	up to 8F or CF

lcd_data('W');
lcd_data('E');
lcd_data('L');
lcd_data('C');
lcd_data('O');
lcd_data('M');
lcd_data('E');
	while(1);
}
