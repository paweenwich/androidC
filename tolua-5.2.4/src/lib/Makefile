# makefile for tolua library

TOLUA=../..

include $(TOLUA)/config

OBJS=	\
	tolua_event.o \
	tolua_is.o \
	tolua_map.o \
	tolua_push.o \
	tolua_to.o

T= $(TOLUA)/lib/libtolua.a

all: $T

$T: $(OBJS)
	$(AR) $@ $(OBJS)
	$(RANLIB) $@

co:
	co -q -f -M $(OPTIONS) $(SRCS) 
	
clean:
	rm -f $(OBJS) 
	
klean:
	rm -f $T

