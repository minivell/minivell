NAME	= minishell

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

SRCS	=

OBJS	= $(SRCS:.c=.o)

LIBFT_DIR = ./libft

all		: $(NAME)

%.o		: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	: $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft
	@echo $(GREEN) "⚡︎	[ minishell ]	Ready to run minishell" $(RESET)

clean	:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo $(YELLOW) "✭	[ libft ]	Removed Object files" $(RESET)
	@$(RM) $(OBJS)
	@echo $(GREEN) "⚡︎	[ minishell ]	Removed Object files" $(RESET)

fclean	: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo $(YELLOW) "✭	[ libft ]	Removed libft.a" $(RESET)
	@$(RM) $(NAME)
	@echo $(GREEN) "⚡︎	[ minishell ]	Removed minishell" $(RESET)

re		:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY	: all clean fclean re

RESET	= "\x1b[0m"
GREY	= "\x1b[30m"
RED		= "\x1b[31m"
GREEN	= "\x1b[32m"
YELLOW	= "\x1b[33m"
BLUE	= "\x1b[34m"
PURPLE	= "\x1b[35m"
CYAN	= "\x1b[36m"
WHITE	= "\x1b[37m"
