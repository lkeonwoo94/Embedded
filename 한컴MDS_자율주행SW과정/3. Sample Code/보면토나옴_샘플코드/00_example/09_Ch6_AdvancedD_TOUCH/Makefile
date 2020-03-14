##########[Embedded C test firmware Makefile]##############
#
# NAME : Makefile - S3C2450 test Firmware Makefile
# Brief history
#----------------------------------------------------------
#
#	2015.08.10, Seonghye : Modified
#
###########################################################

.EXPORT_ALL_VARIABLES:

## If you want to change path, modify here

TOPDIR = C:/cygwin/00_example/09_Ch6_AdvancedD_TOUCH
TOOLPATH = C:/cygwin/GNUARM-4.1.0

CC = $(TOOLPATH)/bin/arm-elf-gcc
LD = $(TOOLPATH)/bin/arm-elf-ld
OBJCOPY	= $(TOOLPATH)/bin/arm-elf-objcopy
OBJDUMP	= $(TOOLPATH)/bin/arm-elf-objdump

LIBCDIR =$(TOOLPATH)/arm-elf
LIBGCCDIR =$(TOOLPATH)/lib/gcc/arm-elf/4.1.0
LIBC =$(TOOLPATH)/arm-elf/lib/libc.a
LIBGCC = $(TOOLPATH)/lib/gcc/arm-elf/4.1.0/libgcc.a

## User library for UART1 Driver
MY_LIB_PATH = $(TOPDIR)/Libraries
LIBUART =  $(MY_LIB_PATH)/libUart1.a


#### Option Definition ####
INCLUDE	=  -I$(TOPDIR)/SOURCE -I$(LIBCDIR)/include -I$(LIBGCCDIR)/include

CFLAGS	+= $(INCLUDE) -g -Wall -Wstrict-prototypes -Wno-trigraphs -O0
CFLAGS	+= -fno-strict-aliasing -fno-common -pipe
CFLAGS += -march=armv4t -mtune=arm9tdmi -fno-builtin -mapcs

LDFLAGS	= -Bstatic -nostartfiles -T ../S3C2450-RAM.ld -Map 2450main.map
OCFLAGS = -O binary -R .note -R .comment -S

2450TEST = MDS2450.bin

all: $(2450TEST)

$(2450TEST) :
	make -C $(TOPDIR)/SOURCE || exit 1

	cp $(TOPDIR)/SOURCE/MDS2450 $(TOPDIR)/output
	$(OBJCOPY) $(OCFLAGS) $(TOPDIR)/SOURCE/MDS2450 $(TOPDIR)/output/$@
	cp $(TOPDIR)/output/MDS2450.bin /tftpboot
clean:
	make -C $(TOPDIR)/SOURCE clean
	rm -f $(TOPDIR)/output/$(2450TEST)
	rm -f $(TOPDIR)/output/MDS2450

dep:
	make -C $(TOPDIR)/SOURCE dep
