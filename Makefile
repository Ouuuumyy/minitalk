NAME1 = client
NAME2 = server

SRC1 = client.c\
	helper_funcs.c
SRC2 = server.c\
	helper_funcs.c

OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)

CC = gcc
FLAGS = -Werror -Wextra -Wall

all : $(NAME1) $(NAME2)

$(NAME1) : $(OBJ1)
		$(CC) $(FLAGS) $(OBJ1) -o $(NAME1)
	
$(NAME2) : $(OBJ2)
		$(CC) $(FLAGS) $(OBJ2) -o $(NAME2)

clean : 
	rm -f $(OBJ1) $(OBJ2)

fclean : clean
	rm -f $(NAME1) $(NAME2)

re : fclean all

.PHONY : re fclean clean all
 
