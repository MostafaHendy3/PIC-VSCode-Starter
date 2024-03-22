#include <xc.h>
#include <pic16f877a.h>
// Configuration bits
#pragma config FOSC = HS       // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer disabled
#pragma config PWRTE = ON       // Power-up Timer enabled
#pragma config BOREN = OFF      // Brown-out Reset disabled
#pragma config LVP = OFF        // Low-Voltage Programming disabled
#pragma config CPD = OFF        // Data memory code protection off
#pragma config WRT = OFF        // Flash Program Memory Write protection off
#pragma config CP = OFF         // Flash Program Memory Code Protection off

#define _XTAL_FREQ 8000000     // 20 MHz crystal oscillator frequency

int main() {

    TRISB0 = 0;                 // RB0 as output
    while(1) {
        RB0 = 1;                // LED ON
        __delay_ms(500);        // Delay 500ms
        RB0 = 0;                // LED OFF
        __delay_ms(500);        // Delay 500ms
    }
    return 0;
}
