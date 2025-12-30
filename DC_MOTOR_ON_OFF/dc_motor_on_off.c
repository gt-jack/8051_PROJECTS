#include <reg51.h>

sbit MOTOR = P1^0;   // L293D IN1
sbit SW = P3^2;      // Switch

void main()
{
    MOTOR = 1;       // Motor OFF initially

    while(1)
    {
        if(SW == 0)  // Switch pressed
            MOTOR = 0;   // Motor ON
        else
            MOTOR = 1;   // Motor OFF
    }
}
