# Trabalho Final da Disciplina de OMIC
# Piano de 8 teclas

Por favor, certifique-se de que o seu ATMega328P está executando com clock de 1MHz
  - Para mudar seu clock para 1MHz, execute o comando em seu terminal com o Microcontrolador ligado a uma porta USB:
    avrdude -b 9600 -p m328p -c usbasp -e -U lfuse:w:0x62:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m

Montagem e linkedição dentro dos códigos (1a e 2a linha)

Buzzer deve estar conectado a porta PB1!
