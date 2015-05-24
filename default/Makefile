###############################################################################
# Makefile for the project niedziela1
###############################################################################

## General Flags
PROJECT = niedziela1
MCU = atmega128
TARGET = niedziela1.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -DF_CPU=16000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=niedziela1.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = niedziela1.o usart_bms.o wyglad_wyswietlacza.o S1D15705.o graphic.o obsluga_eeprom.o crc.o timer1.o obsluga_ADC.o obliczanie_szerokosci_paskow.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) niedziela1.hex niedziela1.eep niedziela1.lss size

## Compile
niedziela1.o: ../niedziela1.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart_bms.o: ../usart_bms.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

wyglad_wyswietlacza.o: ../wyglad_wyswietlacza.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

S1D15705.o: ../S1D15705.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

graphic.o: ../graphic.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

obsluga_eeprom.o: ../obsluga_eeprom.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

crc.o: ../crc.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

timer1.o: ../timer1.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

obsluga_ADC.o: ../obsluga_ADC.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

obliczanie_szerokosci_paskow.o: ../obliczanie_szerokosci_paskow.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) niedziela1.elf dep/* niedziela1.hex niedziela1.eep niedziela1.lss niedziela1.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

