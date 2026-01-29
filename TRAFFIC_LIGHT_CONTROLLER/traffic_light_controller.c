#include <reg51.h>

/* Road 1 */
sbit R1_G = P2^0;
sbit R1_Y = P2^1;
sbit R1_R = P2^2;

/* Road 2 */
sbit R2_G = P2^3;
sbit R2_Y = P2^4;
sbit R2_R = P2^5;

/* Road 3 */
sbit R3_G = P2^6;
sbit R3_Y = P2^7;
sbit R3_R = P1^0;

/* Road 4 */
sbit R4_G = P1^1;
sbit R4_Y = P1^2;
sbit R4_R = P1^3;

void delay(unsigned int sec) {
    unsigned int i, j;
    for(i=0;i<sec;i++)
        for(j=0;j<20000;j++);
}

void all_red() {
    R1_R=R2_R=R3_R=R4_R=0;  // RED ON
    R1_G=R2_G=R3_G=R4_G=1;  // GREEN OFF
    R1_Y=R2_Y=R3_Y=R4_Y=1;  // YELLOW OFF
}

void main() {
    while(1) {

        // Road 1
        all_red();
        R1_R = 1;
        R1_G = 0;
        delay(10);
        R1_G = 1; R1_Y = 0;
        delay(3);
        R1_Y = 1;

        // Road 2
        all_red();
        R2_R = 1;
        R2_G = 0;
        delay(10);
        R2_G = 1; R2_Y = 0;
        delay(3);
        R2_Y = 1;

        // Road 3
        all_red();
        R3_R = 1;
        R3_G = 0;
        delay(10);
        R3_G = 1; R3_Y = 0;
        delay(3);
        R3_Y = 1;

        // Road 4
        all_red();
        R4_R = 1;
        R4_G = 0;
        delay(10);
        R4_G = 1; R4_Y = 0;
        delay(3);
        R4_Y = 1;
    }
}
