#########[MDS2450 test firmware src Makefile]#########
# 
#	Programmer: Son Seong Hye  (2015/08/10)
# 
###################################################### 

CSRCS = $(wildcard *.c)
COBJS = $(CSRCS:.c=.o)

ASRCS = $(wildcard *.S)
AOBJS = $(ASRCS:.S=.o)

SRCS = $(CSRCS) $(ASRCS)
OBJS = $(COBJS) $(AOBJS)

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