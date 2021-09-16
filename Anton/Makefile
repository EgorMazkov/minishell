NAME = minishell

HEADER = minishell.h

SRC = main.c libft/ft_strncmp.c

READLINE = -L/Users/$(USER)/.brew/Cellar/readline/8.1/lib/ -lreadline

FLAGS = -Wall -Wextra -Werror

OBJ = ${SRC:.c=.o}

all : ${NAME}

%.o : %.c $(HEADER)
	gcc ${FLAGS} -c $< -o $@

${NAME} : ${SRC} ${OBJ}
	gcc ${FLAGS} ${READLINE} -o ${NAME} ${SRC}
	./minishell

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re