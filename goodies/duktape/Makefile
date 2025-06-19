EXE:=duktape

DEPLOY_PATH = usr/bin

all : $(EXE)

TARGET_PATH = ../../buildroot/output/target
PREFIX:=../../buildroot/output/host/bin/riscv32-buildroot-linux-uclibc-
CC:=$(PREFIX)gcc
OBJDUMP:=$(PREFIX)objdump

CFLAGS?=-march=rv32ima -mabi=ilp32 -fPIE -pie -Os -s -static
LDFLAGS?=-Wl,-elf2flt="-r -s 196608"

DUKTAPEVER:=duktape-2.7.0
DUKTAPEBLD:=src-noline
CFLAGS+=-I$(DUKTAPEVER)/$(DUKTAPEBLD)

C_S+=$(DUKTAPEVER)/$(DUKTAPEBLD)/duktape.c
C_S+=$(DUKTAPEVER)/examples/cmdline/duk_cmdline.c
C_S+=$(DUKTAPEVER)/extras/console/duk_console.c
CFLAGS+=-DDUK_CMDLINE_CONSOLE_SUPPORT -I$(DUKTAPEVER)/extras/console

$(EXE) : $(DUKTAPEVER)
	$(CC) $(C_S) $(CFLAGS) $(LDFLAGS) -o $@
	$(OBJDUMP) -S $@.gdb > $@.S

deploy : $(EXE)
	cp $^ $(TARGET_PATH)/$(DEPLOY_PATH)
	cp fizzbuzz.js $(TARGET_PATH)/root

# sudo apt-get install node node-js-yaml node-yamlish python-yaml

$(DUKTAPEVER) :
	wget https://duktape.org/$(DUKTAPEVER).tar.xz -O $(DUKTAPEVER).tar.xz
	tar xvpf $(DUKTAPEVER).tar.xz

clean :
	rm -rf $(EXE) $(EXE).gdb $(EXE).S duktape-*


