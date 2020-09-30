//avr-g++ -Wall -Os -mmcu=atmega328p -o storms song_of_storms.cpp
//avrdude -b 9600 -p m328p -c usbasp -e -U flash:w:storms

// Make it Rain!

#define F_CPU 1000000UL
#define TIMER1_PRESCALER 8

#include <avr/io.h>
#include <util/delay.h>

// OCR1A values
const uint16_t C4_FREQ = 262;
const uint16_t D4_FREQ = 292;
const uint16_t E4_FREQ = 330;
const uint16_t F4_FREQ = 349;
const uint16_t G4_FREQ = 392;
const uint16_t A4_FREQ = 440;
const uint16_t B4_FREQ = 494;

const uint16_t C5_FREQ = 523;
const uint16_t D5_FREQ = 587;
const uint16_t E5_FREQ = 659;
const uint16_t F5_FREQ = 698;

#define C4 (F_CPU / (C4_FREQ * TIMER1_PRESCALER * 2) - 1)
#define D4 (F_CPU / (D4_FREQ * TIMER1_PRESCALER * 2) - 1)
#define E4 (F_CPU / (E4_FREQ * TIMER1_PRESCALER * 2) - 1)
#define F4 (F_CPU / (F4_FREQ * TIMER1_PRESCALER * 2) - 1)
#define G4 (F_CPU / (G4_FREQ * TIMER1_PRESCALER * 2) - 1)
#define A4 (F_CPU / (A4_FREQ * TIMER1_PRESCALER * 2) - 1)
#define B4 (F_CPU / (B4_FREQ * TIMER1_PRESCALER * 2) - 1)

#define C5 (F_CPU / (C5_FREQ * TIMER1_PRESCALER * 2) - 1)
#define D5 (F_CPU / (D5_FREQ * TIMER1_PRESCALER * 2) - 1)
#define E5 (F_CPU / (E5_FREQ * TIMER1_PRESCALER * 2) - 1)
#define F5 (F_CPU / (F5_FREQ * TIMER1_PRESCALER * 2) - 1)


int main(void)
{
   // OC1A pino saida
   DDRB = (1 << PINB1);
   DDRD &= ~(1<<PD0);
   DDRD &= ~(1<<PD1);
   DDRD &= ~(1<<PD2);

   // Timer1, modo CTC, prescaler 8
   TCCR1A = (1 << COM1A0);
   TCCR1B = (1 << WGM12)|(1 << CS11);;

    while (1)
    { 
        OCR1A = D4;   
        _delay_ms(1500);
        OCR1A = F4;   
        _delay_ms(1250);
        OCR1A = D5;   
        _delay_ms(6000);

        OCR1A = D4;   
        _delay_ms(1500);
        OCR1A = F4;   
        _delay_ms(1250);
        OCR1A = D5;   
        _delay_ms(6000);

        OCR1A = E5;   
        _delay_ms(5000);
        OCR1A = F5;   
        _delay_ms(1250);
        OCR1A = E5;   
        _delay_ms(1250);
        OCR1A = F5;   
        _delay_ms(1250);
        OCR1A = E5;   
        _delay_ms(1250);
        OCR1A = C5;   
        _delay_ms(1250);
        OCR1A = A4;   
        _delay_ms(6250);

        OCR1A = A4;   
        _delay_ms(2500);
        OCR1A = D4;   
        _delay_ms(2500);
        OCR1A = F4;   
        _delay_ms(1250);
        OCR1A = G4;   
        _delay_ms(1250);
        OCR1A = A4;   
        _delay_ms(6250);

        OCR1A = A4;   
        _delay_ms(2500);
        OCR1A = D4;   
        _delay_ms(3750);
        OCR1A = F4;   
        _delay_ms(1250);
        OCR1A = G4;   
        _delay_ms(2000);
        OCR1A = E4;   
        _delay_ms(6000);


        OCR1A = D4;   
        _delay_ms(1500);
        OCR1A = F4;   
        _delay_ms(1200);
        OCR1A = D5;   
        _delay_ms(6000);

        OCR1A = D4;   
        _delay_ms(1500);
        OCR1A = F4;   
        _delay_ms(1200);
        OCR1A = D5;   
        _delay_ms(6000);

        OCR1A = E5;   
        _delay_ms(5000);
        OCR1A = F5;   
        _delay_ms(1250);
        OCR1A = E5;   
        _delay_ms(1250);
        OCR1A = F5;   
        _delay_ms(1250);
        OCR1A = E5;   
        _delay_ms(1250);
        OCR1A = C5;   
        _delay_ms(1250);
        OCR1A = A4;   
        _delay_ms(6250);

        OCR1A = A4;   
        _delay_ms(2500);
        OCR1A = D4;   
        _delay_ms(2500);
        OCR1A = F4;   
        _delay_ms(1250);
        OCR1A = G4;   
        _delay_ms(1250);
        OCR1A = A4; 

        _delay_ms(6250);
        OCR1A = A4;   
        _delay_ms(2500);
        OCR1A = D4;   
        _delay_ms(8000);
        
        OCR1A = 0;
        _delay_ms(5000);   
    }
}
