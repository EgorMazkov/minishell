SRCS		=	ft_memset.c ft_bzero.c ft_calloc.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_memset.c ft_strlen.c ft_strdup.c ft_split.c \
				ft_strlcat.c ft_strlcpy.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_strnstr.c \
				ft_isprint.c ft_toupper.c ft_tolower.c ft_strmapi.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
BONUS		=	ft_lstnew.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
OBJS		=	${SRCS:.c=.o}
BONUS_OBJS	=	$(BONUS:.c=.o)
INCS		=	includes
NAME		=	libft.a
GCC			=	gcc
ARRC		=	ar rc
RLIB		=	ranlib
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror -g
.c.o:
				@${GCC} ${CFLAGS} -c $< -o ${<:.c=.o} -I${INCS}

all:			${NAME}

${NAME}:		${OBJS}
				@${ARRC} ${NAME} ${OBJS}
				@${RLIB} ${NAME}

bonus:			$(BONUS_OBJS)
				@${ARRC} ${NAME} ${BONUS_OBJS}
				@${RLIB} ${NAME}

clean:
				@${RM} ${OBJS} ${BONUS_OBJS}

fclean:			clean
				@${RM} ${NAME}

re:				fclean all
