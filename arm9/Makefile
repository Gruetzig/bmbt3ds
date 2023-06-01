# Define the target architecture and compiler
ARCH = armv5te
CC = arm-none-eabi-gcc


# Define the source files
SOURCES = source
INCLUDE = $(foreach dir, $(SOURCES), -I$(dir))
SFILES	= $(foreach dir, $(SOURCES), $(wildcard $(dir)/*.s))
CFILES	= $(foreach dir, $(SOURCES), $(wildcard $(dir)/*.c))

# Define the object files that will be generated from the source files
C_OBJECTS = $(CFILES:.c=.o)
ASM_OBJECTS = $(SFILES:.s=.o)
OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)

# Define the name of the target executable
ELF = arm9.elf

# Define the flags to be passed to the compiler
CFLAGS = -DARM9 -I$(INCLUDE) -march=$(ARCH) -mthumb -O2 -Wall
LDFLAGS = -T link.ld -Wl,--nmagic -lm -nostartfiles
 
# Define the default target to build when no target is specified
all: $(ELF) $(OBJECTS)

# Define a rule to build the target executable
$(ELF): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# Define a rule to build the C object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Define a rule to build the ASM object files
%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@


# Define a rule to clean up the project directory
clean:
	rm $(ELF)
	cd source
	rm -f $(OBJECTS)
	cd ..