NAME = philo
SRC_D = mandatory
SRC = $(SRC_D)/philo.c $(SRC_D)/parcing.c $(SRC_D)/libft0.c
OBJ = $(SRC:.c=.o)
CC = cc
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(SRC_D)/%.o: $(SRC_D)/%.c $(SRC_D)/philo.h Makefile
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all
