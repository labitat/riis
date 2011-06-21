CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
AVRDUDE = avrdude
STTY = stty
ARDUINO_HEADERS = .

NAME = riis

MCU = atmega328p
F_CPU = 16000000UL
FORMAT = ihex

## Duemilanove
#PORT = /dev/ttyUSB0
#BAUD_RATE = 57600

## Uno
PORT = /dev/ttyACM0
BAUD_RATE = 115200

PROGRAMMER = arduino
CFLAGS = -O2 -g -mmcu=$(MCU) -DF_CPU=$(F_CPU) \
         -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums \
         -Wall -Wextra -pedantic -I$(ARDUINO_HEADERS)

.PHONY: all list stty
.PRECIOUS: %.o %.elf

all: $(NAME).hex

%.o: %.c %.h
	@echo '  CC $@'
	@$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	@echo '  CC $@'
	@$(CC) $(CFLAGS) -c $< -o $@

%.elf: %.o
	@echo '  LD $@'
	@$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

%.hex: %.elf
	@echo '  OBJCOPY $@'
	@$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@ && \
		stat --format='  %s bytes' $@

# Create extended listing file from ELF output file.
%.lss: %.elf
	@echo '  OBJDUMP $@'
	@$(OBJDUMP) -h -S $< > $@

upload: $(NAME).hex
	@$(AVRDUDE) -vD -c$(PROGRAMMER) -b$(BAUD_RATE) -p$(MCU) -P$(PORT) -Uflash:w:$<:i

list: $(NAME).lss

tty:
	@echo '  STTY -F$(PORT) cs8 parenb raw -echo 57600'
	@$(STTY) -F$(PORT) cs8 parenb raw -echo 57600

clean:
	rm -f *.o *.elf *.hex *.lss
