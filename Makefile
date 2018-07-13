CC = g++ -g
STDFLAGS = -std=c++11

all: prog3

prog3:
	$(CC) prog3.cc main.cc -o $@ $(STDFLAGS)

.PHONY: clean

clean:
	rm -rf prog3