#
# proc_bs
#
# (C) 2020.03.14 BuddyZhang1 <buddy.zhang@aliyun.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
ifneq ($(KERNELRELEASE),)

# SRC
obj-m		:= proc.o
proc-m		+= base.o
proc-m		+= fd.o
proc-m		+= generic.o
proc-m		+= inode.o
proc-m		+= proc_sysctl.o
proc-m		+= root.o
proc-m		+= self.o
proc-m		+= sysctl.o
proc-m		+= thread_self.o
proc-m		+= util.o
ccflags-y	+= -DCONFIG_BISCUITOS_TMPFS_BLOCKS=0x1000
ccflags-y	+= -DCONFIG_BISCUITOS_TMPFS_INODES=0x1000

else
## Parse argument
ifeq ("$(origin BSROOT)", "command line")
BSROOT=$(BSROOT)
else
BSROOT=/xspace/OpenSource/BiscuitOS/BiscuitOS/output/linux-5.0-arm32
endif

ifeq ("$(origin ARCH)", "command line")
ARCH=$(ARCH)
else
ARCH=arm
endif

ifeq ("$(origin CROSS_TOOLS)", "command line")
CROSS_TOOLS=$(CROSS_TOOLS)
else
CROSS_TOOLS=arm-linux-gnueabi
endif

# Don't Edit
KERNELDIR=$(BSROOT)/linux/linux
CROSS_COMPILE_PATH=$(BSROOT)/$(CROSS_TOOLS)/$(CROSS_TOOLS)/bin
CROSS_COMPILE=$(CROSS_COMPILE_PATH)/$(CROSS_TOOLS)-
INCLUDEDIR=$(KERNELDIR)/include
ARCHINCLUDEDIR=$(KERNELDIR)/arch/$(ARCH)/include
INSTALLDIR=$(BSROOT)/rootfs/rootfs/

## X86/X64 Architecture
ifeq ($(ARCH), i386)
CROSS_COMPILE	:=
else ifeq ($(ARCH), x86_64)
CROSS_COMPILE	:=
endif

# Compile
AS		= $(CROSS_COMPILE)as
LD		= $(CROSS_COMPILE)ld
CC		= $(CROSS_COMPILE)gcc
CPP		= $(CC) -E
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm
STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump

# FLAGS
CFLAGS += -I$(INCLUDEDIR) -I$(ARCHINCLUDEDIR)

all: $(OBJS)
	make -C $(KERNELDIR) M=$(PWD) ARCH=$(ARCH) \
                CROSS_COMPILE=$(CROSS_COMPILE) modules

install:
	make -C $(KERNELDIR) M=$(PWD) ARCH=$(ARCH) \
		INSTALL_MOD_PATH=$(INSTALLDIR) modules_install
	@chmod 755 RunBiscuitOS_proc.sh
	@cp -rfa RunBiscuitOS_proc.sh $(BSROOT)/rootfs/rootfs/usr/bin

clean:
	@rm -rf *.ko *.o *.mod.o *.mod.c *.symvers *.order \
               .*.o.cmd .tmp_versions *.ko.cmd .*.ko.cmd

endif
