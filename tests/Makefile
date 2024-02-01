##
## EPITECH PROJECT, 2024
## lib
## File description:
## Makefile
##

CC = g++

NAME = ../unit_tests

TESTS_SRC 	= 	JsonParserSpec.cpp\
				Main.cpp\

TESTS_OBJ = $(TESTS_SRC:.cpp=.o)

SRC	=	../JsonParser/JsonParser.cpp

OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -Wall -Wextra -Werror -std=c++20 --coverage

CPPFLAGS = -iquote./pipunit/include -iquote../include

all: $(NAME)

$(NAME): $(TESTS_OBJ) $(OBJ)
	make -C ./pipunit
	$(CC) -o $(NAME) $(TESTS_OBJ) $(OBJ) -L./pipunit -lpipunit --coverage

clean:
	rm -f $(TESTS_OBJ)
	rm -f $(OBJ)
	make clean -C ./pipunit

fclean: clean
	rm -f $(NAME)
	make fclean -C ./pipunit

re: fclean all

.PHONY: all clean fclean re
