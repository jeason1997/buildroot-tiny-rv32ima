TARGET = hello_linux
DEPLOY_PATH = usr/bin
C_S=main.c

all : $(TARGET)

TARGET_PATH = ../../buildroot/output/target
PREFIX:=../../buildroot/output/host/bin/riscv32-buildroot-linux-uclibc-
CC:=$(PREFIX)gcc
OBJDUMP:=$(PREFIX)objdump

CFLAGS:=-mabi=ilp32 -fPIE -pie -static -march=rv32ima -Os -s
LDFLAGS:=-Wl,-elf2flt=-r 

$(TARGET) : $(C_S)
	$(CC) $(CFLAGS) $(C_S) $(LDFLAGS) -o $@
	$(OBJDUMP) -S $@.gdb > $@.S

deploy : $(TARGET)
	cp $^ $(TARGET_PATH)/$(DEPLOY_PATH)

clean :
	rm -rf $(TARGET) $(TARGET).gdb $(TARGET).S
