#include makefile.inc
CC=g++
CFLAGS=-pthread -std=c++14 -Wall -g
INC=-Isrc
CCC=$(CC) $(CFLAGS) $(INC)
LD=$(CC)

PROJS := src/util src/screen src/snake

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
