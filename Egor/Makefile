NAME		=	push_swap

SRCS_FILES	= 	${shell find ./source -name "*.c"}

SRCS_FOLDER	=	source/

SRCS		= 	$(SRCS_FILES)
OBJS		=	$(patsubst %.c,%.o,$(SRCS))

INCLUDE		=	-I./include -I./libs/libft/

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f

LIB = ./libs/libft/libft.a

.PHONY:		all clean fclean re bonus

all:		$(NAME)

%.o:		%.c
			@$(CC) $(CFLAGS) $(INCLUDE) -c -g $< -o $@ 
$(NAME):	$(OBJS)
			$(MAKE) -C $(dir $(LIB))
			$(CC) $(INCLUDE) $(LIB) -o $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS)
			@make -C $(dir $(LIB)) clean

fclean:		clean
			@make -C $(dir $(LIB)) fclean
			$(RM) $(NAME)

re:			fclean all

norm:
	norminette