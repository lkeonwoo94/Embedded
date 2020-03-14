#########[MDS2450 test firmware src Makefile]#########
# 
#	Programmer: Son Seong Hye  (2015/08/10)
# 
###################################################### 

SRCS	= s3c2450_startup.S libs.S  libc.c  Main.c Uart.c timer.c \
			key.c

OBJS	= s3c2450_startup.o  libc.o libs.o Main.o Uart.o timer.o \
			key.o

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