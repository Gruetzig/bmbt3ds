# Define the name of the target executable
EXECUTABLE = bmbt3ds
ARM9ELF = arm9/arm9.elf
# ARM11ELF = arm11.elf

# Define the default target to build when no target is specified
all: $(EXECUTABLE).firm

.PHONY: $(ARM9ELF)

# Define a rule to build the arm9 elf file
$(ARM9ELF):
	@echo Building arm9 $@
	@make --no-print-directory -C arm9

# Define a rule to build the arm11 elf file
#$(ARM11ELF):
#	make --no-print-directory -C arm11

#Define a rule to build the firm file
$(EXECUTABLE).firm: $(ARM9ELF)
	@echo building $@
	@firmtool build $@ -n 0x08006000 -e 0 -D $< -A 0x08006000 -C memcpy -i
#	firmtool build $@ -n 0x08006000 -e 0 -D $(ARM9ELF) $(ARM11ELF) -A 0x08006000 -C memcpy -i
	@cp $(EXECUTABLE).firm boot.firm

clean:
	@make --no-print-directory -C arm9 clean
#   @make --no-print-directory -C arm11 clean
	@rm -f $(EXECUTABLE).firm
	@rm -f boot.firm