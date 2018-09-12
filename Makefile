##

# uncomment to see the actual commandlines
Q = @

# which programs to use
CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump

# c flags to select the right processor
CFLAGS=-I. -Iinclude/ -g -nostartfiles -mthumb -mcpu=cortex-m0

# ldscript to
LDSCRIPT = lib/SWM050.ld

#library files
OBJ = lib/crt0.o lib/SWM500_flash.o lib/SWM500_tmrse.o lib/system_SWM500.o
OBJ += lib/SWM500_exti.o lib/SWM500_gpio.o lib/SWM500_wdt.o

# projectfile(s)
OBJ += main.o
PROJECT = blinky

%.o: %.c 
	@printf "  CC      $(*).c\n"
	$(Q)$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.s
	@printf "  AS      $(*).s\n"
	$(Q)$(CC) -c -o $@ $^ $(CFLAGS)

$(PROJECT).elf: $(OBJ)
	@printf "  LD      $(@)\n"
	$(Q)$(CC) -o $@ $^ $(CFLAGS) -T $(LDSCRIPT)

%.bin: %.elf
	@printf "  OBJCOPY $(*).bin\n"
	$(Q)$(OBJCOPY) -Obinary $(*).elf $(*).bin

%.asm: %.elf
	@printf "  OBJDUMP $(*).asm\n"
	$(Q)$(OBJDUMP) -d $(*).elf > $(PROJECT).asm

all:	$(PROJECT).elf $(PROJECT).bin $(PROJECT).asm

.PHONY: clean

clean:
	@rm -f *.o *~ core ./lib/*.o $(PROJECT).elf $(PROJECT).bin $(PROJECT).asm

