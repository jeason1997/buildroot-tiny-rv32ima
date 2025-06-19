all : deploy

DEPLOY_PATH = usr/bin
TARGET_PATH = ../../buildroot/output/target

PREFIX := ../../buildroot/output/host/bin/riscv32-buildroot-linux-uclibc-
CC := $(PREFIX)gcc

CFLAGS:=-mabi=ilp32 -fPIE -pie -static -march=rv32ima -Os -s -g
LDFLAGS:=-Wl,-elf2flt=-r

C_S+=c4src/c4.c

c4src :
	git clone https://github.com/tvlad1234/c4.git c4src

c4 : c4src
	$(CC) $(CFLAGS) $(C_S) $(LDFLAGS) -o $@

deploy : c4
	cp $^ $(TARGET_PATH)/$(DEPLOY_PATH)
	mkdir -p $(TARGET_PATH)/usr/src
	cp $(C_S) $(TARGET_PATH)/usr/src
	cp c4src/hello.c $(TARGET_PATH)/root

clean :
	rm -rf c4 c4.gdb c4src
