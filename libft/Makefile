NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

INC = ./

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_strncmp.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_strndup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strcmp.c

SRCS_b = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJS = ${SRCS:.c=.o}

OBJS_b = ${SRCS_b:.c=.o}


ifdef BONUS
	OBJS_T = ${OBJS} ${OBJS_b}
else
	OBJS_T = ${OBJS}
endif

${NAME}:	${OBJS_T}
			@ar -rc ${NAME} ${OBJS_T}

all:	${NAME}


.c.o:
	@${CC} ${CFLAGS} -c $< -o $@ -I${INC}

bonus:
		@make BONUS=1 all

clean:
		@rm -f ${OBJS} ${OBJS_b}

fclean: clean
		@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
