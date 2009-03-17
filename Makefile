makefile:
all: postnmr

clean:
	-rm main.o postnmr.exe postnmr

postnmr: main.o
	g++ -g -o postnmr main.o

main.o: main.cpp
	g++ -c -g main.c