.global main
	.type main, @function
main:
	ldi r16, 0b00000011
	out 0x4, r16
LOOP:
	out 0x5, r16
	jmp LOOP

