##
## EPITECH PROJECT, 2024
## lib
## File description:
## Makefile
##

CC = g++

RM = rm -f

NAME = libmy.a

SRC = 	JsonParser/JsonParser.cpp\
		ArgsParser/ArgsParser.cpp\

OBJ = $(SRC:.cpp=.o)

CXXFLAGS += -iquote./include -Wall -Wextra -Werror -std=c++20

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

unit_tests:
	make -C ./tests

clean:
	$(RM) $(OBJ)
	make clean -C ./tests

fclean: clean
	$(RM) $(NAME)
	$(RM) *~
	$(RM) */*.gc*
	make fclean -C ./tests

re: fclean all

test: re
	$(CC) $(CXXFLAGS) -o test main.cpp $(NAME)

.PHONY: all clean fclean re test
