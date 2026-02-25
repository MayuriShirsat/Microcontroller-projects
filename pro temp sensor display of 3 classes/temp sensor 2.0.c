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

unsigned char adc_data;
char buffer[10];

void delay(unsigned int ms) {
    unsigned int i, j;
    for(i=0; i<ms; i++)
        for(j=0; j<1275; j++);
}

void delay_sec(void){
	unsigned int i;
	for(i=0;i<=5000;i++){ //delay of 1 sec
	TMOD=0x01; //timer 0 mode 1
	TH0=0xFC;
	TL0=0x66;
	TR0=1;
	while(TF0==0);
		TR0=0;
		TF0=0;
	  }
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
    unsigned char _data;
    unsigned int temp;
    unsigned char int_part, dec_part;	//don't declare again and again if need many time declare once at top
	
	  lcd_init();
	
	  while(1){
			  _data=start(0);
			
			   temp = (_data * 500) / 255; 
         int_part = temp / 10;
         dec_part = temp % 10;     

	       lcd_cmd(0x01); //clear display
	       lcd_cmd(0x80); //line1			
			   lcd_string("A_class Temp:");  
         lcd_cmd(0xC0); //line2			
			   sprintf(buffer, "%d.%d C", int_part, dec_part);
		     lcd_string(buffer);
			   delay_sec();
			
			   _data=start(1);
			   temp = (_data * 500) / 255; 
         int_part = temp / 10;
         dec_part = temp % 10; 
			
	       lcd_cmd(0x01); 
	       lcd_cmd(0x80); 		
			   lcd_string("B_class Temp:");
         lcd_cmd(0xC0);				 
			   sprintf(buffer, "%d.%d C", int_part, dec_part);
		     lcd_string(buffer);			
			   delay_sec();
			
			   _data=start(2);
         temp = (_data * 500) / 255; 
         int_part = temp / 10;
         dec_part = temp % 10;  
				 
	       lcd_cmd(0x01); 
	       lcd_cmd(0x80); 		
			   lcd_string("C_class Temp:");
         lcd_cmd(0xC0);
         sprintf(buffer, "%d.%d C", int_part, dec_part);
		     lcd_string(buffer);
						 
	      delay_sec();
	}
}