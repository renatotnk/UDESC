.global main
	.type main, @function
main:
	ldi r16, 0b00000001
	out 0x4, r16
LOOP:
	out 0x5, r16
	call delay_omic
	jmp LOOP

delay_omic:
	#a função destrói o conteúdo de r16 e r17. Cuidado
	ldi  r16, 0x01 ; carrega 0xFF para r16
	ldi  r17, 0x01 ; carrega 0xFF para r17
	jmp delay_loop
delay_loop:
	nop
	nop
	nop
	nop
	nop
	nop
	dec  r16 ; decremente 1 de r17
	brne delay_loop ;salta se o flag ZERO não está setado
	dec  r17 ; decrementa r16
	brne delay_loop ; salta se o flag ZERO não está setado
	out 0x5, r17
	ret

