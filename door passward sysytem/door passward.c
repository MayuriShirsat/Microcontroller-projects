#include <reg51.h>

#define keypad P1  // Port1 connected to keypad
#define lcd P2     // Port2 connected to LCD

sbit rs = P3^0;
sbit en = P3^1;
sbit door = P3^2;

// Lookup table for 4x4 keypad
char keymap[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};
/*Pull-up resistors: Columns must be kept HIGH when idle.

Use internal pull-ups of 8051 (already there on Port1), so no extra resistors needed.*/

void delay(unsigned int ms){
    unsigned int i,j;
    for(i=0;i<ms;i++)
        for(j=0;j<1275;j++);
}

void lcd_cmd(unsigned char cmd){
    rs=0;
    lcd=cmd;
    en=1; delay(2); en=0;
}

void lcd_data(unsigned char dat){
    rs=1;
    lcd=dat;
    en=1; delay(2); en=0;
}

void lcd_init(){
    lcd_cmd(0x38); // 8-bit mode
    lcd_cmd(0x0C); // Display on
    lcd_cmd(0x06); // Auto increment
    lcd_cmd(0x01); // Clear screen
}

void lcd_string(char *str){
    while(*str) lcd_data(*str++);
}

// Function to scan keypad
char keypad_scan(){
    unsigned char row, col;
    for(row=0; row<4; row++){
        keypad = 0xF0;         // Make cols input, rows output
        keypad &= ~(1<<row);   // Drive one row LOW
        for(col=0; col<4; col++){
            if(!(keypad & (0x10<<col))){ // Check column
                while(!(keypad & (0x10<<col))); // Wait for release
                return keymap[row][col]; // Return pressed key
            }
        }
    }
    return 0; // No key pressed
}

void main(){
	  unsigned int i,j;
    unsigned char set_pass[7];
		unsigned char enter_pass[7];
	  unsigned char correct;
	
    lcd_init();
    lcd_cmd(0x80);
    lcd_string("SET PASSWORD(7 DIGITS)");
    
    for(i=0;i<=6;i++){
        set_pass[i] = keypad_scan();
        if(set_pass[i]){
            lcd_cmd(0xC0);   // Move to 2nd row
            lcd_data(set_pass[i]);   
        }
    }
    lcd_cmd(0x01);		
    lcd_string("PASSWORD IS SET");
    delay(2000);
		
	for(j=0;j<3;j++){			
    lcd_cmd(0x01);		
    lcd_string("ENTER PASSWORD");
		lcd_cmd(0xC0);

		for(i=0;i<=6;i++){
        enter_pass[i] = keypad_scan();
			  lcd_data('*'); // hide entered
		}
		
    correct = 1;
    for(i=0; i<=6; i++){
        if(set_pass[i] != enter_pass[i]){
            correct = 0;
            break;
        }
    }		
			  if(correct){
		      lcd_cmd(0x01);
          lcd_string("DOOR OPEN");										
					door = 1;
					delay(9000);
					door = 0;
          while(1); // stop here dont check further					
				}else{
			    lcd_cmd(0x01);				
          lcd_string("WRONG PASSWORD");										
					delay(2000);
				}
		}
		lcd_cmd(0x01);
    lcd_string("SYSTEM LOCKED");
    door = 0;
    while(1); // lock permanently		
}
/*P3.2 ->1k resistor -> Base of NPN transistor
Emitter -> GND
Collector -> one end of relay coil
Other end of relay coil -> +12V
Diode (1N4007) across relay coil (protection)
Relay contacts -> Door Lock (12V Solenoid or Motor)
Relay/Motor ? +12V (with separate supply, but common GND with 8051)
*/