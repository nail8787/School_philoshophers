NAME = philo_three

SRC = philo_three.c print.c init.c ft_atoi.c check.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Werror -Wextra
HEADER = philo_three.h

all: $(NAME)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(HEADER)
	gcc $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all