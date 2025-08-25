TARGET = hello_linux
DEPLOY_PATH = usr/bin
C_S=main.c

BUILD_DIR = build

BINARY = $(BUILD_DIR)/$(TARGET)

all : $(BINARY)

TARGET_PATH = ../../buildroot/output/target
PREFIX:=../../buildroot/output/host/bin/riscv32-buildroot-linux-uclibc-

CC:=$(PREFIX)gcc
OBJDUMP:=$(PREFIX)objdump

CFLAGS:=-mabi=ilp32 -fPIE -pie -static -march=rv32ima -Os -s
LDFLAGS:=-Wl,-elf2flt=-r 

$(BUILD_DIR) :
	mkdir -p $@

$(BINARY) : $(C_S) $(BUILD_DIR)
	$(CC) $(CFLAGS) $(C_S) $(LDFLAGS) -o $@
	$(OBJDUMP) -S $@.gdb > $@.S

deploy : $(BINARY)
	cp $^ $(TARGET_PATH)/$(DEPLOY_PATH)

clean :
	rm -rf $(TARGET_PATH)/$(DEPLOY_PATH)/$(BINARY) build
