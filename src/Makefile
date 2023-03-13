CC = g++

TARGET = test

PROG_NAME = test

MATH_SRCS = math/base.cpp math/Num.cpp
SYNTAX_SRCS = syntax/interp.cpp syntax/lex.cpp syntax/parse.cpp syntax/Token.cpp
SRCS = $(MATH_SRCS) $(SYNTAX_SRCS)

all: $(TARGET).cpp
	clear
	$(CC) -o $(PROG_NAME) $(TARGET).cpp $(SRCS)
