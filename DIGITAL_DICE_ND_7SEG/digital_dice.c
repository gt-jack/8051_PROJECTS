#include <reg51.h>

sbit SW = P3^2;   // Push button

// 7-segment codes for numbers 1 to 6 (COMMON CATHODE)
unsigned char dice[6] =
{
    0x06,  // 1
    0x5B,  // 2
    0x4F,  // 3
    0x66,  // 4
    0x6D,  // 5
    0x7D   // 6
};

void delay_ms(unsigned int ms);

void main()
{
    unsigned char rand;

    SW = 1;           // Switch as input
    TMOD = 0x01;      // Timer0 Mode 1 (16-bit)
    TR0 = 1;          // Start Timer0

    while(1)
    {
        if(SW == 0)   // Button pressed
        {
            rand = TL0 % 6;      // Generate random number (0–5)
            P1 = dice[rand];    // Display random number

            delay_ms(300);      // Debounce delay
        }
    }
}

void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 1275; j++);
}
