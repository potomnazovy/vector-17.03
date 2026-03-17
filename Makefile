CXXFLAGS += -Wall -Wextra -std=c++14

main: main.o
	g++ $^ -o $@