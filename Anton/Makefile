NAME = minishell

HEADER = minishell.h

SRC = main.c

READLINE = -L/Users/$(USER)/.brew/Cellar/readline/8.1/lib/ -lreadline

FLAGS = -Wall -Wextra -Werror

OBJ = ${SRC:.c=.o}

INCLUDE = -I./libft

all : ${NAME}

%.o : %.c $(HEADER)
	gcc ${FLAGS} -c $< -o $@

${NAME} : ${SRC} ${OBJ}
	@gcc $(FLAGS) $(INCLUDE) -c -g $< -o $@
	gcc ${FLAGS} ${READLINE} -o ${NAME} ${SRC}
	./minishell

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re