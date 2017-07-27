##
## Makefile for keylogger in /home/azword/delivery/Perso/PSU/Keylogger/
##
## Made by Nathan Tréhout
## Login   <nathan.trehout@epitech.eu>
##
## Started on  Sat Dec 31 15:30:40 2016 Nathan Tréhout
##

CC	=	gcc -g

NAME	=	generator

SRC	=	src/main.c		\
		src/get_next_line.c	\

LIB	=	

CFLAGS	=	-I./include/ #-W -Wall -Wextra -pedantic

RM	=	rm -fr $(NAME)

all	:	$(NAME)


$(NAME)	:
		$(CC) -o $(NAME) $(SRC) $(CFLAGS) $(LIB)

debug   :
		$(CC) -o $(NAME) $(SRC) $(CFLAGS) $(LIB) -DDebug

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME_BONUS)


re	:	fclean all

