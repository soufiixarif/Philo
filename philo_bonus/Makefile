NAME = philo_bonus
SRC_D = .
SRC = $(SRC_D)/data_init_bonus.c $(SRC_D)/parcing_bonus.c $(SRC_D)/libft_bonus.c $(SRC_D)/philo_bonus.c $(SRC_D)/simulation_bonus.c $(SRC_D)/time.c
OBJ = $(SRC:.c=.o)
CC = cc
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(SRC_D)/%.o: $(SRC_D)/%.c $(SRC_D)/philo_bonus.h Makefile
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all