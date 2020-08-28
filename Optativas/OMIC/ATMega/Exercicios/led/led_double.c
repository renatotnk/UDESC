#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

int main( ){

	DDRB = 0b00000001;
	double count = 0;
	while(1){
		if(count < 5){
			PORTB = 0b00000001;
			_delay_ms(1000);
			PORTB = 0b00000000;
			_delay_ms(1000);
		}else{
    		PORTB = 0b00000001;
			_delay_ms(500);
			PORTB = 0b00000000;
			_delay_ms(500);
		}
		if (count < 5){
			count++;
		}
	}
}
