CPP = g++

CFLAGS = -O3 -Werror -Wpedantic -Wall -Wextra
appname = test

CXXFLAGS :=  -O3 

all: main.cpp
	$(CPP) -O3 -Werror -Wpedantic -Wall -Wextra -std=c++17 -g -o output main.cpp
clean:
	rm -f $(appname) *.o
.PHONY: all clean
