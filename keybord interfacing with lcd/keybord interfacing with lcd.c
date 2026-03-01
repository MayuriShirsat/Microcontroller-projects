#include <reg51.h>

#define keypad P1     // Keypad ? Port1
#define lcd P2        // LCD Data ? Port2

sbit rs = P3^7;
sbit en = P3^6;
sbit led = P3^0;

/* Keypad Map */
char keymap[4][3]={
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};

/* Delay */
void delay(unsigned int ms){
    unsigned int i,j;
    for(i=0;i<ms;i++)
        for(j=0;j<1275;j++);
}

/* LCD COMMAND */
void lcd_cmd(unsigned char cmd){
    rs=0;
    lcd=cmd;
    en=1;
    delay(5);
    en=0;
}

/* LCD DATA */
void lcd_data(unsigned char dat){
    rs=1;
    lcd=dat;
    en=1;
    delay(5);
    en=0;
}

/* LCD STRING */
void lcd_string(char *str){
    while(*str)
        lcd_data(*str++);
}

/* LCD INIT */
void lcd_init(){
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
}

/* KEYPAD SCAN (CORRECT VERSION) */
char keypad_scan(){
    unsigned char row;

    for(row=0;row<4;row++){

        keypad = 0xF0;              // Columns HIGH
        keypad &= ~(1<<row);        // One row LOW

        if(!(keypad & 0x10)){ delay(200); return keymap[row][0]; }
        if(!(keypad & 0x20)){ delay(200); return keymap[row][1]; }
        if(!(keypad & 0x40)){ delay(200); return keymap[row][2]; }
    }
    return 0;
}

/* MAIN PROGRAM */
void main(){

unsigned char i,j;
unsigned char set_pass[7];
unsigned char enter_pass[7];
unsigned char correct;
char key;

lcd_init();

lcd_cmd(0x80);
lcd_string("SET PASSWORD");

/* SET PASSWORD */
for(i=0;i<7;i++){
    while(!(key=keypad_scan()));
    set_pass[i]=key;

    lcd_cmd(0xC0+i);
    lcd_data(key);
}

delay(2000);

/* PASSWORD CHECK */
for(j=0;j<3;j++){

    lcd_cmd(0x01);
    lcd_string("ENTER PASSWORD");

    for(i=0;i<7;i++){
        while(!(key=keypad_scan()));
        enter_pass[i]=key;

        lcd_cmd(0xC0+i);
        lcd_data('*');
    }

    correct=1;

    for(i=0;i<7;i++){
        if(set_pass[i]!=enter_pass[i]){
            correct=0;
            break;
        }
    }

    if(correct){
        lcd_cmd(0x01);
        lcd_string("ACCESS GRANTED");

        led=1;
        delay(9000);
        led=0;

        while(1);
    }
    else{
        lcd_cmd(0x01);
        lcd_string("WRONG PASSWORD");
        delay(2000);
    }
}

lcd_cmd(0x01);
lcd_string("SYSTEM LOCKED");
led=0;

while(1);
}