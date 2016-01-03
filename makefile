#include makefile.inc
CC=g++
CFLAGS+=-pthread
CFLAGS+=-std=c++14
CFLAGS+=-Wall
CFLAGS+=-g
LDFLAGS+=-framework CoreFoundation
LDFLAGS+=-framework AudioToolbox
INC+=-Isrc
INC+=-I3py
CCC=$(CC) $(CFLAGS) $(INC)
LD=$(CC) $(LDFLAGS)

PROJS := src/util src/screen src/snake 3py/auplay

SRCS := $(shell find $(PROJS) -type f -name "*.cpp")
HDRS := $(shell find $(PROJS) -type f -name "*.h")
OBJS := $(patsubst %.cpp,%.o,$(SRCS))
#DEPS := $(patsubst %.cpp,%.d,%(SRCS))
#ALLS := $(SRCS)

all: $(OBJS)
	$(LD) $(OBJS) -o snake.x

%.o: %.cpp $(HDRS)
	$(CCC) -c $< -o $@
	
clean:
	rm -f $(OBJS)
