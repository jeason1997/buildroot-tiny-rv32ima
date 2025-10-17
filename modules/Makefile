obj-m += tinyrv32ima_spi.o
ARCH ?= riscv
MYY_KERNEL_DIR ?= $(PWD)/buildroot/output/build/linux-6.6.18
CROSS_COMPILE ?= $(PWD)/buildroot/output/host/bin/riscv32-buildroot-linux-uclibc-
INST_PATH ?= $(PWD)/buildroot/output/target 
MOD_SRC_PATH ?= $(PWD)/modules

all: install

modules: 
	+make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=$(MOD_SRC_PATH) -C $(MYY_KERNEL_DIR) modules

clean:
	+make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=$(MOD_SRC_PATH) INSTALL_MOD_PATH=$(INST_PATH) -C $(MYY_KERNEL_DIR) clean

install: modules
	+make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=$(MOD_SRC_PATH) INSTALL_MOD_PATH=$(INST_PATH) -C $(MYY_KERNEL_DIR) modules_install
	