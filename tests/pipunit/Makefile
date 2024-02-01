##
## EPITECH PROJECT, 2024
## pipunit
## File description:
## Makefile
##

CC = g++

NAME = libpipunit.a

SRC = 	src/Test.cpp	\
		src/Redirect.cpp	\


OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -Wall -Wextra -Werror -std=c++17
CPPFLAGS = -iquote./include

all: $(NAME)

$(NAME): $(OBJ)
	ar rc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CXXFLAGS += -g3
debug: re

.PHONY: all clean fclean re debug
