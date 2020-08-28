#constantes
.equ DDRB, 0x04
.equ DDRD, 0x0A
.equ PORTB, 0x05
.equ PIND, 0x09

	.global main
	.type main, @function
main:
	ldi r16, 0b00000011
	out DDRB, r16 	;
	eor r16, r16 	; XOR em r16(ou carregue 0 para r16)
	out DDRD, r16	; todos os pinos de PORTD como entrada
LOOP:
	ldi r17, 0b00000000 ; carregue constante 0
	in r16, PIND
	sbrc r16, 0		; pule a prox. inst.se o bit 7 estásetado
	inc r17			; some 1 em r17
	inc r17			; some 1 em r17
	out PORTB, r17
	jmp LOOP


