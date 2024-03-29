##
## EPITECH PROJECT, 2021
## Project_2021
## File description:
## Project makefile
##

DSRC	= ./src/
CC 		= gcc

SRC =	 	$(DSRC)realloc.c		\
			$(DSRC)realloc_optimise.c \
			$(DSRC)malloc.c			\
			$(DSRC)free.c			\
			$(DSRC)calloc.c			\
			$(DSRC)math.c			\
			$(DSRC)env.c			\
			$(DSRC)list/split_block.c	\
			$(DSRC)list/create.c		\
			$(DSRC)list/find.c			\
			$(DSRC)list/fusion.c		\
			$(DSRC)list/move_break.c	\
			$(DSRC)list/utility.c		\
			$(DSRC)thread.c				\

SRC_UT = ./tests/tests_malloc.c \
		$(SRC)

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy_malloc.so
NAME_TEST = test_malloc.out

CFLAGS		+= -fPIC -W -Wall -Wextra $(INCLUDE) -Werror
CXXFLAGS    +=
DEBUG 	= -g 
INCLUDE = -I./includes

all:  $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) -lm -shared && \
		$(ECHO) $(BOLD_T)$(GREEN_C)"\n[✔] COMPILED:" $(DEFAULT)$(LIGHT_GREEN) "$(NAME)\n"$(DEFAULT) || \
		$(ECHO) $(BOLD_T)$(RED_C)"[✘] "$(UNDLN_T)"BUILD FAILED:" $(LIGHT_RED) "$(NAME)\n"$(DEFAULT)

clean:
	rm -f  $(OBJ)
	rm -f *.gcda
	rm -f *.gcno

fclean:	clean
	rm -f $(NAME)

re:	fclean all

reall:	fclean all

tests_run: $(NAME)
	@gcc -o $(NAME_TEST) $(SRC_UT) $(INCLUDE) -lcriterion --coverage -lm -ldl \
		&& LD_PRELOAD=./$(NAME) ./$(NAME_TEST)		\
		&& rm -f $(NAME_TEST)

.PHONY :        clean fclean re

ECHO	=	/bin/echo -e
DEFAULT	=	"\e[0m"
BOLD_T	=	"\e[1m"
DIM_T	=	"\e[2m"
UNDLN_T	=	"\e[4m"
BLACK_C	=	"\e[30m"
RED_C	=	"\e[31m"
GREEN_C	=	"\e[32m"
YELLO_C	=	"\e[33m"
BLUE_C	=	"\e[34m"
MAGEN_C	=	"\e[35m"
CYAN_C	=	"\e[36m"
WHITE_C	=	"\e[97m"
DEFAULT_C	=	"\e[39m"
LINE_RETURN	=	$(ECHO) ""
