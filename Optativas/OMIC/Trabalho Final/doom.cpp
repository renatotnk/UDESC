//avr-g++ -Wall -Os -mmcu=atmega328p -o doom doom.cpp
//avrdude -b 9600 -p m328p -c usbasp -e -U flash:w:doom
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
const uint16_t A4S_FREQ = 466;
const uint16_t B4_FREQ = 494;

const uint16_t C5_FREQ = 523;
const uint16_t C5S_FREQ = 554;
const uint16_t D5_FREQ = 587;
const uint16_t D5S_FREQ = 622;
const uint16_t E5_FREQ = 659;
const uint16_t F5_FREQ = 698;
const uint16_t F5S_FREQ = 740;
const uint16_t G5_FREQ = 784;
const uint16_t G5S_FREQ = 831;
const uint16_t A5_FREQ = 880;
const uint16_t B5_FREQ = 988;



#define C4 (F_CPU / (C4_FREQ * TIMER1_PRESCALER * 2) - 1)
#define D4 (F_CPU / (D4_FREQ * TIMER1_PRESCALER * 2) - 1)
#define E4 (F_CPU / (E4_FREQ * TIMER1_PRESCALER * 2) - 1)
#define F4 (F_CPU / (F4_FREQ * TIMER1_PRESCALER * 2) - 1)
#define G4 (F_CPU / (G4_FREQ * TIMER1_PRESCALER * 2) - 1)
#define A4 (F_CPU / (A4_FREQ * TIMER1_PRESCALER * 2) - 1)
#define A4S (F_CPU / (A4S_FREQ * TIMER1_PRESCALER * 2) - 1)
#define B4 (F_CPU / (B4_FREQ * TIMER1_PRESCALER * 2) - 1)

#define C5 (F_CPU / (C5_FREQ * TIMER1_PRESCALER * 2) - 1)
#define C5S (F_CPU / (C5S_FREQ * TIMER1_PRESCALER * 2) - 1)
#define D5 (F_CPU / (D5_FREQ * TIMER1_PRESCALER * 2) - 1)
#define D5S (F_CPU / (D5S_FREQ * TIMER1_PRESCALER * 2) - 1)
#define E5 (F_CPU / (E5_FREQ * TIMER1_PRESCALER * 2) - 1)
#define F5 (F_CPU / (F5_FREQ * TIMER1_PRESCALER * 2) - 1)
#define F5S (F_CPU / (F5S_FREQ * TIMER1_PRESCALER * 2) - 1)
#define G5 (F_CPU / (G5_FREQ * TIMER1_PRESCALER * 2) - 1)
#define G5S (F_CPU / (G5S_FREQ * TIMER1_PRESCALER * 2) - 1)
#define A5 (F_CPU / (A5_FREQ * TIMER1_PRESCALER * 2) - 1)
#define B5 (F_CPU / (B5_FREQ * TIMER1_PRESCALER * 2) - 1)


int main(void)
{
   // OC1A pino saida
   DDRB = (1 << PINB1);
   DDRD &= ~(1<<PD0);
   DDRD &= ~(1<<PD1);
   DDRD &= ~(1<<PD2);
   //DDRD &= ~(1<<PD3);
   //DDRD &= ~(1<<PD4);

   // Timer1, modo CTC, prescaler 8
   TCCR1A = (1 << COM1A0);
   TCCR1B = (1 << WGM12)|(1 << CS11);;

    while (1)
    {   
        for(unsigned int i = 0; i < 3; i++){
            OCR1A = E4;   
            _delay_ms(1000);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E5;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = D5;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = C5;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = A4S;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = B4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = C4;   
            _delay_ms(1200);

            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E5;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = D5;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = C5;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = A4S;   
            _delay_ms(6000);

            OCR1A = 0;   
            _delay_ms(1000);
        }

        OCR1A = E4;   
            _delay_ms(1000);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E5;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = D5;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = C5;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = A4S;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = B4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = C4;   
            _delay_ms(1200);

            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E5;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = D5;   
            _delay_ms(1200);


            OCR1A = F5S;   
            _delay_ms(700);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = D5;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = B4;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = A5;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = F5S;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = B4;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = D5;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = F5S;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = A5;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = F5S;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = D5;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = B4;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);

            OCR1A = 0;   
            _delay_ms(500);

        for(unsigned int i = 0; i < 1; i++){
            OCR1A = E4;   
            _delay_ms(1000);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E5;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = D5;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = C5;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = A4S;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = B4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = C4;   
            _delay_ms(1200);

            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E5;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = D5;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = C5;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = A4S;   
            _delay_ms(6000);

            OCR1A = 0;   
            _delay_ms(1000);
        }

        OCR1A = E4;   
            _delay_ms(1000);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E5;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = D5;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = C5;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = A4S;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = B4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = C4;   
            _delay_ms(1200);

            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E5;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = E4;   
            _delay_ms(1200);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = D5;   
            _delay_ms(1200);


            OCR1A = F5S;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = D5;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = B4;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = A5;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = F5S;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = B4;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = D5;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = F5S;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = A5;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = F5S;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = D5;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);
            OCR1A = B4;   
            _delay_ms(600);
            OCR1A = 0;   
            _delay_ms(50);

            OCR1A = 0;   
            _delay_ms(1000);
    
    }
}
