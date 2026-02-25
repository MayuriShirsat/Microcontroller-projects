#include <reg51.h>

#define keypad P1  // Port1 connected to keypad
#define lcd P2     // Port2 connected to LCD

sbit rs = P3^0;
sbit en = P3^1;

// Lookup table for 4x4 keypad
char keymap[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

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
    lcd_cmd(0x38); 
    lcd_cmd(0x0C); 
    lcd_cmd(0x06); 
    lcd_cmd(0x01); 
}

void lcd_string(char *str){
    while(*str) lcd_data(*str++);
}

// Function to scan keypad
char keypad_scan(){
    unsigned char row, col;
	
    for(row=0; row<4; row++){//The function activates one row at a time.
        keypad = 0xF0;         // Make columns(P1.7 to P1.4) input, rows(P1.3 to P1.0) output
//P1.7 P1.6......P1.0 ->1111 0000
			keypad &= ~(1<<row);   
/*Suppose we have a 4×4 keypad, and we are scanning row 2
1)First, (1 << row) -> 1 << 2 = 0000 0100
2)Then, ~(1 << row) -> bitwise NOT -> 1111 1011
initially keypad value = 1111 1111
3)1111 1111 AND 1111 1011 = 1111 1011
Only row 2 bit became 0, rest stayed 1			
*/
        for(col=0; col<4; col++){//Check each column one by one to see if a key is pressed.
            if(!(keypad & (0x10<<col))){ 
/*(0x10 << col) -> selects column bit (P1.4–P1.7)
col=0 -> P1.4, col=1 -> P1.5, col=2 -> P1.6, col=3 -> P1.7
keypad & (0x10 << col) -> reads the column value	
(keypad & 0x20) = 0 -> !(0) = 1 -> key detected*/							
                while(!(keypad & (0x10<<col))); // Wait for release (debouncing)
                return keymap[row][col]; // Return pressed key
            }
        }
    }
    return 0; // return 0 if No key pressed
}

void main(){
    char key;
    lcd_init();
    lcd_cmd(0x80);
    lcd_string("Keypad Test");
    
    while(1){
        key = keypad_scan();
        if(key){
            lcd_cmd(0xC0);   // Move to 2nd row
            lcd_data(key);   // Display pressed key
        }
    }
}
