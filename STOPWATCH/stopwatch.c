#include <reg51.h>

/* LCD Control Pins */
sbit RS = P2^0;
sbit RW = P2^1;
sbit EN = P2^2;

/* Push Buttons (Active LOW) */
sbit START = P3^0;
sbit STOP  = P3^1;
sbit RESET = P3^2;

/* Global Variables */
unsigned int sec = 0, min = 0;
bit run = 0;

/* Function Prototypes */
void delay_ms(unsigned int ms);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char dat);
void lcd_init(void);
void lcd_print(unsigned int m, unsigned int s);

/* LCD Command */
void lcd_cmd(unsigned char cmd) {
    P1 = cmd;
    RS = 0;
    RW = 0;
    EN = 1;
    delay_ms(2);
    EN = 0;
}

/* LCD Data */
void lcd_data(unsigned char dat) {
    P1 = dat;
    RS = 1;
    RW = 0;
    EN = 1;
    delay_ms(2);
    EN = 0;
}

/* LCD Initialization */
void lcd_init(void) {
    lcd_cmd(0x38);   // 8-bit, 2-line
    lcd_cmd(0x0C);   // Display ON
    lcd_cmd(0x01);   // Clear
    lcd_cmd(0x80);   // Cursor home
}

/* Display MM:SS */
void lcd_print(unsigned int m, unsigned int s) {
    lcd_cmd(0x80);
    lcd_data((m/10) + '0');
    lcd_data((m%10) + '0');
    lcd_data(':');
    lcd_data((s/10) + '0');
    lcd_data((s%10) + '0');
}

/* 1 ms Delay using Timer0 */
void delay_ms(unsigned int ms) {
    unsigned int i;
    for(i = 0; i < ms; i++) {
        TMOD = 0x01;      // Timer0 Mode1
        TH0  = 0xFC;
        TL0  = 0x66;
        TR0  = 1;
        while(TF0 == 0);
        TR0  = 0;
        TF0  = 0;
    }
}

/* Main Program */
void main(void) {
    P3 = 0xFF;   // Enable internal pull-ups for buttons

    lcd_init();
    lcd_print(min, sec);

    while(1) {

        if(START == 0) run = 1;
        if(STOP  == 0) run = 0;

        if(RESET == 0) {
            min = 0;
            sec = 0;
            run = 0;
            lcd_print(min, sec);
        }

        if(run) {
            unsigned int i;

            /* Non-blocking 1 second delay */
            for(i = 0; i < 1000; i++) {
                delay_ms(1);

                if(STOP == 0) {
                    run = 0;
                    break;
                }

                if(RESET == 0) {
                    min = 0;
                    sec = 0;
                    run = 0;
                    lcd_print(min, sec);
                    break;
                }
            }

            if(run) {
                sec++;
                if(sec == 60) {
                    sec = 0;
                    min++;
                }
                lcd_print(min, sec);
            }
        }
    }
}
