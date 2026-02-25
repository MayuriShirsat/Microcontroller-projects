#include<reg51.h>
#include<stdio.h>

sbit X=P1^0;
sbit Y=P1^1;
sbit Z=P1^2;
sbit SOC=P1^3;
sbit ALE=P1^4;
sbit OE=P1^5;
sbit EOC=P1^6;
sbit rs=P3^0;
sbit en=P3^1;
sbit fan=P3^2;

/*cannot connect a 12V fan directly to 8051 pin. The pin can only source/sink a few mA.
P3.2 -> Resistor -> Base of NPN transistor  
Emitter -> GND  
Collector -> One end of relay/fan  
Other end -> Vcc (12V for fan)  

WHY THEY NEED->
1)NPN Transistor
The 8051 gives a small base current ? transistor allows a larger current to flow from collector to emitter (to fan/relay).

2)Relay Module
Needed if fan is AC or higher voltage DC (like 12V/24V).
A relay is an electrically operated switch that lets a low-voltage circuit (8051 + transistor) control a high-voltage circuit (fan).
Relay coil energizes ? mechanical contacts close ? AC/DC fan gets power.
Relay coil de-energizes ? contacts open ? fan OFF.

3)Diode (1N4007) Across Relay Coil
When relay coil is switched OFF, the collapsing magnetic field generates a back EMF (high reverse voltage spike).
This can damage the transistor and microcontroller.
The diode protects the transistor & MCU from voltage spikes when the relay switches OFF.
*/

unsigned char adc_data;
char buffer[10];

void delay(unsigned int ms) {
    unsigned int i, j;
    for(i=0; i<ms; i++)
        for(j=0; j<1275; j++);
}

void lcd_data(unsigned char xyz){
	rs=1;
	P2=xyz;
	en=1;
	delay(5);
	en=0;
}

void lcd_cmd(unsigned char xyz){
	rs=0;
	P2=xyz;
	en=1;
	delay(5);
	en=0;
}

void lcd_init() {		
    lcd_cmd(0x38);  
    lcd_cmd(0x0C);  
    lcd_cmd(0x06);  
    lcd_cmd(0x01);  
    delay(2);
}

void lcd_string(char *str){
    while(*str) lcd_data(*str++);
}
unsigned char start(unsigned char channel){ 
  X = channel & 0x01;
	Y = (channel >> 1) & 0x01;
  Z = (channel >> 2) & 0x01;

	ALE=1;
	delay(1);
	ALE=0;
	SOC=1;
	delay(1);	
	SOC=0;
	
while(EOC==1);
    OE=1;
	  adc_data=P0;
		OE=0;
		return adc_data; 
}

void main(){
	  lcd_init();
	  lcd_cmd(0x80);  //set cursor at first row of LCD
	  lcd_string("Temp:");   
	
	  while(1){
			  unsigned char _data = start(0);

			  unsigned int temp = (_data * 500) / 255; //same project can be used for display voltage
        unsigned char int_part = temp / 10;  //Split TEMP into integer & decimal   
        unsigned char dec_part = temp % 10;     
			  sprintf(buffer, "%d.%d C", int_part, dec_part);
	      lcd_cmd(0xC0);        
		    lcd_string(buffer);
        
			  if(int_part>=30){
					fan=1;
				}else if(int_part<28){
					fan=0;
				}
				
	      delay(100);
	}
}
