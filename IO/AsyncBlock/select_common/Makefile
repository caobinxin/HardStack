#
# Syscall: sys_mkdir
#
# (C) 2020.03.10 BuddyZhang1 <buddy.zhang@aliyun.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.

# Install PATH
ifeq ($(INSPATH), )
INSTALL_PATH=./
else
INSTALL_PATH=$(INSPATH)
endif

# CROSS_COMPILE form argument

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
LCFLAGS += -I./ -fomit-frame-pointer

# SRC
SRC += client.c

# Target
ifeq ($(TARGETA), )
TARGET=select
else
TARGET=$(TARGETA)
endif

all:
	@$(CC) $(LCFLAGS) -o $(TARGET)-client  client.c
	@$(CC) $(LCFLAGS) -o $(TARGET)-service service.c

install:
	@cp -rfa $(TARGET)-client  $(INSTALL_PATH)
	@cp -rfa $(TARGET)-service $(INSTALL_PATH)

clean:
	@rm -rf *.ko *.o *.mod.o *.mod.c *.symvers *.order \
               .*.o.cmd .tmp_versions *.ko.cmd .*.ko.cmd $(TARGET)-*
