#include<reg51.h>
#include<stdio.h>
sbit RS = P2^0;
sbit EN = P2^1;

unsigned char hour = 12,min = 0,sec = 0;

void delay_ms(unsigned int ms){ //this type of delay is used to get accurate delay of 1 sec insted of for loop delay
	unsigned int i;
	for(i=0; i<ms; i++){ 
	TMOD=0x01; 
	TH0=0xFC;//1 ms from FC66 H to FFFF	H	we can use 0000 to ffff in 14 cycle insted of 1000 but it is not preferable
	TL0=0x66;
	TR0=1;
	while(TF0==0);
		TR0=0;
		TF0=0;
	}
}

// 1 second delay
void delay_s() {
    delay_ms(1000);   // 1000 × 1 ms = 1 sec
}

void lcd_cmd(unsigned char cmd) {
    P1 = cmd;
    RS = 0;
    EN = 1;
    delay_ms(2);
    EN = 0;
}

void lcd_data(unsigned char da) {
    P1 = da;
    RS = 1;
    EN = 1;
    delay_ms(2);
    EN = 0;
}

void lcd_init() {		//commands of LCD
    lcd_cmd(0x38);  
    lcd_cmd(0x0C);  
    lcd_cmd(0x06);  
    lcd_cmd(0x01);  
}

void lcd_string(char *str) {
    while(*str != '\0') {
        lcd_data(*str++);
    }
}

void update_time(){
		if(sec==60){
		 	sec=0;
			min++;
		 }
		if(min==60){
		 	min=0;
			hour++;		
	  }
			if(hour==24){
		 	hour=0;
    }
	}	

void main() {
	
	      char buffer[16];//to store the sec in integer form as LCD can not read integers (except:"1","0")	
	      lcd_init();//call				
        lcd_cmd(0x80);      // row 1 start
			  lcd_string("HH:MM:SS");	
	
	while(1){
		
        lcd_cmd(0xC0);                 // Second row
        lcd_string("            ");    // Clear previous content
        lcd_cmd(0xC0);
		
        sprintf(buffer, "%02d:%02d:%02d", hour, min, sec);
   			
				lcd_string(buffer);//pass to string to display
			  delay_s();
			  sec++;
        update_time();
  }
}



/*8051 Timer Limits
Mode 0->	13-bit->	8192	8192 × 1.085 µs ˜ 8.9 ms->	TH0=0x00, TL0=0x00 (full)->	1 s / 0.0089 s = ˜ 112
Mode 1->	16-bit->  65536	65536 × 1.085 µs ˜ 71.1 ms->	TH0=0x00, TL0=0x00 (full)->	1 s / 0.0711 s  =˜ 14
Mode 2->	8-bit auto-reload->	256	256 × 1.085 µs ˜ 0.277 ms->	TH0 = 0x00 (full), TL0 auto-reloads->	1 s / 0.000277 s = ˜ 3610
Mode 3->	Split Timer->	TL0 & TH0 8-bit->	256 × 1.085 µs ˜ 0.277 ms per 8-bit->	TL0/TH0 = 0x00 (full)->	1 s / 0.000277 s = ˜ 361*/