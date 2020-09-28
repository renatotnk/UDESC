# Montagem e linkedição
;avr-gcc -Wall -Os -mmcu=atmega328p -o trab_final trab_final.s
;avrdude -b 9600 -p m328p -c usbasp -e -U flash:w:trab_final

#Lembretes de definições de melhores constantes
; melhor prescaler = 1/8
; p pegar valores, rodar script python

;constantes
.equ RAMEND, 0x8FF	;ultima posicao de memoria
.equ SPH, 0x3E		;endereco de memoria de SPH
.equ SPL, 0x3D		;endereco de memoria de SPl
.equ SREG, 0x3F
.equ TCCR1A, 0x80	; Registrador de clock(parte alta)
.equ TCCR1B, 0x81	; Registrador de clock(parte baixa)
.equ OCR1AH,0x89	; Output compare register A High
.equ OCR1AL,0x88	; Output compare register A Low

# Portas de dados e I/O
.equ DDRB, 0x04
.equ DDRC, 0x07
.equ DDRD, 0x0A
.equ PORTB, 0x05
.equ PINC, 0x06
.equ PIND, 0x09

#Para definir frequencia de saída, fazer o cálculo
; No modo CTC, OCR1AL = ((1*10⁶ - ((2* freq_nota) * prescaler)) / ((2* freq_nota) * prescaler))) 

#Notas
.equ C4, 0xED	; 262
.equ D4, 0xD3	; 294
.equ E4, 0xBC	; 330
.equ F4, 0xB2	; 349
.equ G4, 0x9E	; 392
.equ A4, 0x8D	; 440
.equ B4, 0x7D	; 494
.equ C5, 0x76	; 523

	.global main
	.type main, @function
main:
	#ajuse do stack pointer(por precaucao)
	ldi r16, hi8(RAMEND)
	ldi r17, lo8(RAMEND)
	out SPL, r17
	out SPH, r16
	#fim do ajuste do stack pointer

	# Config. pinos I/O
	ldi r16, 0b00000010	; Porta PB1(OC1A) como saída
	out DDRB, r16	

	ldi r16, 0b00000000	; 0 em r16
	out DDRD, r16	; Todos os pinos de PD como entrada
	out DDRC, r16

	# configuracao regs TCCR1A e TCCR1B
	ldi r16, 0b01000000	; Habilitando OC1A como saída para frequencia
	sts TCCR1A, r16
	ldi r16, 0b00001010	; Habilitando modo CTC, prescaler de 1/8		
	sts TCCR1B, r16	

	# Inicializando regs zerados
	ldi r16, 0b00000000
	ldi r31, 0b00000000
	ldi r25, 0b00000000

LOOP:
	# Limpando regs
	clr r16
	clr r25
	clr r31

	# Limpando Registrador de comparação do clock
	clr r18
	sts OCR1AH, r18
	sts OCR1AL, r18

	# Lendo pino D de entrada 
	in r16, PIND

	# Chamando função para carregar nota
	rcall load_note

	# Enviando 1 com determinada freq (nota) para o buzzer
	out PORTB, r31
	jmp LOOP

# Delay básico
delay_debounce: ;saltar aqui custa 3 ciclos
	ldi r18,0xFF ;custa 2 ciclos
loop_debounce: ;passa pelo loop R18-1 vezes
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	dec r18 ;custa 1 ciclo
	brne loop_debounce ;custa 2 ciclos (salta), ou 1 ciclo
	ret 	;custa 4 ciclos

load_note:
	cpi r16, 0b00000001
	breq load_C

	cpi r16, 0b00000010
	breq load_D

	cpi r16, 0b00000100
	breq load_E

	cpi r16, 0b00001000
	breq load_F

	cpi r16, 0b00010000
	breq load_G

	cpi r16, 0b00100000
	breq load_A

	cpi r16, 0b01000000
	breq load_B

	cpi r16, 0b10000000
	breq load_C5
	ret

load_C:
	ldi r17, C4
	sts OCR1AL, r17
	ldi r31, 0b00000010
	rcall delay_debounce
	rcall delay_debounce
	#rcall delay_debounce
	ret

load_D:
	ldi r17, D4
	sts OCR1AL, r17
	ldi r31, 0b00000010
	rcall delay_debounce
	rcall delay_debounce
	rcall delay_debounce
	ret

load_E:
	ldi r17, E4
	sts OCR1AL, r17
	ldi r31, 0b00000010
	rcall delay_debounce
	rcall delay_debounce
	rcall delay_debounce
	ret

load_F:
	ldi r17, F4
	sts OCR1AL, r17
	ldi r31, 0b00000010
	rcall delay_debounce
	rcall delay_debounce
	rcall delay_debounce
	rcall delay_debounce
	ret

load_G:
	ldi r17, G4
	sts OCR1AL, r17
	ldi r31, 0b00000010
	rcall delay_debounce
	rcall delay_debounce
	rcall delay_debounce
	rcall delay_debounce
	ret

load_A:
	ldi r17, A4
	sts OCR1AL, r17
	ldi r31, 0b00000010
	rcall delay_debounce
	rcall delay_debounce
	rcall delay_debounce
	rcall delay_debounce
	ret

load_B:
	ldi r17, B4
	sts OCR1AL, r17
	ldi r31, 0b00000010
	rcall delay_debounce
	rcall delay_debounce
	rcall delay_debounce
	rcall delay_debounce
	ret

load_C5:
	ldi r17, C5
	sts OCR1AL, r17
	ldi r31, 0b00000010
	rcall delay_debounce
	rcall delay_debounce
	rcall delay_debounce
	rcall delay_debounce
	ret
