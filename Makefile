NAME	= minishell

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -fsanitize=address -g3
# COMP_FLAGS	= -L/opt/homebrew/opt/readline/lib -lreadline
# OBJS_FLAGS	= -I/opt/homebrew/opt/readline/include

COMP_FLAGS	= -L/usr/local/lib -lreadline				# CLUSTER flag
OBJS_FLAGS	= -I/usr/local/include/readline				# CLUSTER flag
RM		= rm -f

# exec src files
EXEC_SRCS =		./execute/check_num.c\
				./execute/error.c\
				./execute/exec_cmd.c\
				./execute/exec_process.c\
				./execute/execute.c\
				./execute/get_cmd_path.c\
				./execute/get_path.c\
				./execute/init_exec.c\
				./execute/make_new_env.c\
				./execute/single_process.c\
				./execute/multi_process.c\
				./execute/set_for_heredoc.c\
				./execute/set_for_redir.c\
				./execute/unlink_heredoc.c\
				./execute/wait_child.c\
				./builtin/cd.c\
				./builtin/check_n_exec_builtin.c\
				./builtin/echo.c\
				./builtin/env.c\
				./builtin/exit.c\
				./builtin/export.c\
				./builtin/pwd.c\
				./builtin/unset.c\


# parse src files
PARSE_SRCS =	./parse/parse_all.c \
                ./parse/parse_pipe.c \
                ./parse/parse_redir.c \
                ./parse/token.c \
                ./parse/quote.c \
                ./parse/parse_space.c \
                ./parse/redir.c \
                ./parse/cmd.c \
                ./parse/env.c \
                ./parse/init.c \
                ./parse/parse_error.c \
                ./parse/token_check.c \
                ./parse/convert_env.c \
                ./parse/signal.c\
				./parse/free.c \
				./parse/free2.c


SRCS	=	main.c\
			${EXEC_SRCS}\
			${PARSE_SRCS}

OBJS	= $(SRCS:.c=.o)

LIBFT_DIR = ./libft

all		: $(NAME)

%.o		: %.c
	@$(CC) $(CFLAGS) $(OBJS_FLAGS) -c $< -o $@

$(NAME)	: $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(COMP_FLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft
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
