#########[MDS2450 test firmware src Makefile]#########
# 
#	Programmer: Son Seong Hye  (2015/08/10)
# 
###################################################### 

SRCS	= s3c2450_startup.S libs.S Lcd.c libc.c  Main.c Uart.c

OBJS	= s3c2450_startup.o Lcd.o libc.o libs.o Main.o Uart.o

%.o:%.S
	$(CC) -c $(CFLAGS) -o $@ $<

%.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $<

all: $(OBJS)
	$(LD) $(LDFLAGS) -o MDS2450 $(OBJS) $(LIBC) $(LIBGCC) \
	-I$(LIBGCCDIR)/include -I$(LIBCDIR)/include 

clean:
	rm -f *.o 
	rm -f MDS2450

dep:
	$(CC) -M $(INCLUDE) $(SRCS) > .depend

ifeq (.depend,$(wildcard .depend))
include .depend
endif					