SRC     = ./src/
OUT	= ./obj/
OBJS	= $(OUT)main.o $(OUT)Lexer.o $(OUT)Token.o $(OUT)Expr.o $(OUT)Parser.o
SOURCE	= main.cpp Lexer.cpp Token.cpp Expr.cpp Parser.cpp
HEADER	= Lexer.hpp Token.hpp Expr.hpp Parser.hpp
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)rang $(LFLAGS)

$(OUT)main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -o $(OUT)main.o -std=c++17

$(OUT)Lexer.o: $(SRC)Lexer.cpp
	$(CC) $(FLAGS) $(SRC)Lexer.cpp -o $(OUT)Lexer.o -std=c++17

$(OUT)Token.o: $(SRC)Token.cpp
	$(CC) $(FLAGS) $(SRC)Token.cpp -o $(OUT)Token.o -std=c++17

$(OUT)Expr.o: $(SRC)Expr.cpp
	$(CC) $(FLAGS) $(SRC)Expr.cpp -o $(OUT)Expr.o -std=c++17

$(OUT)Parser.o: $(SRC)Parser.cpp
	$(CC) $(FLAGS) $(SRC)Parser.cpp -o $(OUT)Parser.o -std=c++17

clean:
	rm -f $(OUT)*