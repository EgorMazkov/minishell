NAME		=	minishell

SRCS_FILES	= 	source/validator.c \
				source/ajaraguju.c \
				source/assistant_validator.c \
				source/built_in.c \
				source/cd_no_args.c \
				source/cd.c \
				source/echo.c \
				source/env_operation_utils_overwrite.c \
				source/env_operation_utils.c \
				source/env_operations.c \
				source/env.c \
				source/exist.c \
				source/export.c \
				source/free_all.c \
				source/gavn_two.c \
				source/gavn.c \
				source/main.c \
				source/name_pridumayem_vmeste.c \
				source/open_files.c \
				source/parentpipe.c \
				source/parse_redirects.c \
				source/pipe_child.c \
				source/pipe_main.c \
				source/progress_bucksess.c \
				source/pwd.c \
				source/redict_utils.c \
				source/redirects.c \
				source/signal.c \
				source/sort_env.c \
				source/unset.c \
				source/parser/path/check_path.c \
				source/parser/path/way.c \
				source/parser/record/record_cmd.c \
				source/parser/split_for_castom/split_castom_start.c \
				source/parser/split_for_castom/split_castom_utils.c \
				source/parser/split_for_castom/split_for_castom_finish.c \
				source/parser/utils/utils_three.c \
				source/parser/utils/utils_two.c \
				source/inspace.c \
				source/parser/utils/utils.c


SRCS_FOLDER	=	source/

SRCS		= 	$(SRCS_FILES)
OBJS		=	$(patsubst %.c,%.o,$(SRCS))

READLINE = -L/Users/$(USER)/.brew/Cellar/readline/8.1/lib/ -lreadline

INCLUDE		=	-I./include -I./libs/libft/

HEADERMINI	=	./include/minishell.h ./libft/libft.h

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g
RM			=	rm -f

LIB = ./libft/libft.a

.PHONY:		all clean fclean re bonus

all:		$(NAME)

%.o:		%.c $(HEADERMINI)
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
$(NAME):	$(OBJS)
			@$(MAKE) -C $(dir $(LIB))
			@$(CC) $(INCLUDE) ${READLINE} $(LIB) -o $(NAME) $(OBJS)
			@echo "\033[36;1m\nCompiled\n\033[0m"

clean:
			@$(RM) $(OBJS)
			@make -C $(dir $(LIB)) clean
			@echo "\033[36;1m\nCleaning succeed\n\033[0m"

fclean:		clean
			@make -C $(dir $(LIB)) fclean
			@$(RM) $(NAME)
			@echo "\033[32;1m\nAll created files were deleted\n\033[0m"

re:			fclean all
			@echo "\033[35;1m\nRemake done\n\033[0m"

norm:
	@norminette source/
	@norminette include/
	@echo "\033[35;1m\nNorminette done\n\033[0m"