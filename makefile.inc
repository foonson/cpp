CC=g++
CFLAGS=-pthread -std=c++14 -Wall -g
INC=-Isrc
CCC=$(CC) $(CFLAGS) $(INC)
LD=$(CC) $(INC)
