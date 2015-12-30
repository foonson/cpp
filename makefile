#include makefile.inc
CC=g++
CFLAGS=-pthread -std=c++14 -Wall -g
LDFLAGS+=-framework CoreFoundation -framework AudioToolbox
INC=-Isrc -I3py
CCC=$(CC) $(CFLAGS) $(INC)
LD=$(CC) $(LDFLAGS)

PROJS := src/util src/screen src/snake 3py/auplay

SRCS := $(shell find $(PROJS) -type f -name "*.cpp")
HDRS := $(shell find $(PROJS) -type f -name "*.h")
OBJS := $(patsubst %.cpp,%.o,$(SRCS))
DEPS := $(patsubst %.cpp,%.d,%(SRCS))

ALLS := $(SRCS)

all: $(OBJS)
	$(LD) $(OBJS) -o snake.x

%.o: %.cpp $(HDRS)
	$(CCC) -c $< -o $@
	
clean:
	rm -f $(OBJS)
