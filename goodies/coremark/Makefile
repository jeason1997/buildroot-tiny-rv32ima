TARGET:=coremark
DEPLOY_PATH = usr/bin

BUILD_DIR = build
BINARY = $(BUILD_DIR)/$(TARGET)

all : $(BINARY)

TARGET_PATH = ../../buildroot/output/target
PREFIX = ../../buildroot/output/host/bin/riscv32-buildroot-linux-uclibc-

CC := $(PREFIX)gcc
OBJDUMP := $(PREFIX)objdump

CFLAGS?=-march=rv32ima -mabi=ilp32 -fPIE -pie -Os -s -static
LDFLAGS?=-Wl,-elf2flt="-r -s 32768"
BUILD_DIR = build
APPFOLDER:=$(BUILD_DIR)/coremark-1.01

CFLAGS+=-I$(APPFOLDER) -DPERFORMANCE_RUN=1 -I$(APPFOLDER)/linux
C_S+=$(APPFOLDER)/linux/core_portme.c
C_S+=$(APPFOLDER)/core_list_join.c
C_S+=$(APPFOLDER)/core_main.c
C_S+=$(APPFOLDER)/core_matrix.c
C_S+=$(APPFOLDER)/core_state.c
C_S+=$(APPFOLDER)/core_util.c

$(BINARY) : $(BUILD_DIR)/get_src 
	$(CC) $(C_S) $(CFLAGS) -DFLAGS_STR="\"$(CFLAGS)\"" $(LDFLAGS) -o $@
	$(OBJDUMP) -S $@.gdb > $@.S

deploy : $(BINARY)
	cp $^ $(TARGET_PATH)/$(DEPLOY_PATH)

$(BUILD_DIR)/get_src :
	mkdir -p $(BUILD_DIR)
	wget https://github.com/eembc/coremark/archive/refs/tags/v1.01.zip -O $(BUILD_DIR)/v1.01.zip
	unzip -d $(BUILD_DIR) $(BUILD_DIR)/v1.01.zip
	touch $(BUILD_DIR)/get_src

clean :
	rm -rf $(TARGET_PATH)/$(DEPLOY_PATH)/$(TARGET)/$(BINARY) build
