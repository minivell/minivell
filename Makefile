NAME	= minishell

#==========================================
# exec
EXEC	= minishell_exec
# parse
PARSE	= minishell_parse
#==========================================

CC		= cc
CFLAGS	= -Wall -Wextra -Werror #-fsanitize=address -g3
# COMP_FLAGS	= -L/opt/homebrew/opt/readline/lib -lreadline
# OBJS_FLAGS	= -I/opt/homebrew/opt/readline/include

COMP_FLAGS	= -L/usr/local/lib -lreadline				# CLUSTER flag
OBJS_FLAGS	= -I/usr/local/include/readline				# CLUSTER flag
RM		= rm -f

# exec src files
EXEC_SRCS =		exec_main.c\
				./execute/check_num.c\
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
				./builtin/cd.c\
				./builtin/check_n_exec_builtin.c\
				./builtin/echo.c\
				./builtin/env.c\
				./builtin/exit.c\
				./builtin/export.c\
				./builtin/pwd.c\
				./builtin/unset.c\
				./parse/parse_all.c \
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



# parse src files
PARSE_SRCS =	parse_main.c\
				./parse/parse_all.c \
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
				./parse/free.c 


SRCS	=	${EXEC_SRCS}\
			${PARSE_SRCS}

OBJS	= $(SRCS:.c=.o)

#====================================#
# objs for exec
EXEC_OBJS = $(EXEC_SRCS:.c=.o)

# objs for parse
PARSE_OBJS = $(PARSE_SRCS:.c=.o)
#====================================#

LIBFT_DIR = ./libft

all		: $(NAME)

#====================================#
# make exec
execute : $(EXEC)
# make parse
parse : $(PARSE)
#====================================#

%.o		: %.c
	@$(CC) $(CFLAGS) $(OBJS_FLAGS) -c $< -o $@

$(NAME)	: $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(COMP_FLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft
	@echo $(GREEN) "⚡︎	[ minishell ]	Ready to run minishell" $(RESET)

#====================================#
# make for exec
$(EXEC) : $(EXEC_OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(COMP_FLAGS) -o $(EXEC) $(EXEC_OBJS) -L$(LIBFT_DIR) -lft
	@echo $(GREEN) "⚡︎	[ minishell_exec ]	Ready to run minishell_exec" $(RESET)

# make for parse
$(PARSE) : $(PARSE_OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(COMP_FLAGS) -o $(PARSE) $(PARSE_OBJS) -L$(LIBFT_DIR) -lft
	@echo $(GREEN) "⚡︎	[ minishell_parse ]	Ready to run minishell_parse" $(RESET)

#====================================#

clean	:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo $(YELLOW) "✭	[ libft ]	Removed Object files" $(RESET)
	@$(RM) $(OBJS)
	@echo $(GREEN) "⚡︎	[ minishell ]	Removed Object files" $(RESET)

#====================================#
# clean for exec
executeclean	:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo $(YELLOW) "✭	[ libft ]	Removed Object files" $(RESET)
	@$(RM) $(EXEC_OBJS)
	@echo $(GREEN) "⚡︎	[ minishell_exec ]	Removed Object files" $(RESET)

# clean for parse
parseclean	:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo $(YELLOW) "✭	[ libft ]	Removed Object files" $(RESET)
	@$(RM) $(PARSE_OBJS)
	@echo $(GREEN) "⚡︎	[ minishell_parse ]	Removed Object files" $(RESET)

#====================================#

fclean	: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo $(YELLOW) "✭	[ libft ]	Removed libft.a" $(RESET)
	@$(RM) $(NAME)
	@echo $(GREEN) "⚡︎	[ minishell ]	Removed minishell" $(RESET)


#====================================#
# flcean for exec
executefclean	: executeclean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo $(YELLOW) "✭	[ libft ]	Removed libft.a" $(RESET)
	@$(RM) $(EXEC)
	@echo $(GREEN) "⚡︎	[ minishell_exec ]	Removed minishell_exec" $(RESET)

# flcean for parse
parsefclean	: parseclean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo $(YELLOW) "✭	[ libft ]	Removed libft.a" $(RESET)
	@$(RM) $(PARSE)
	@echo $(GREEN) "⚡︎	[ minishell_parse ]	Removed minishell_parse" $(RESET)

#====================================#


re		:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY	: all clean fclean re execute executeclean executefclean parse parseclean parsefclean

RESET	= "\x1b[0m"
GREY	= "\x1b[30m"
RED		= "\x1b[31m"
GREEN	= "\x1b[32m"
YELLOW	= "\x1b[33m"
BLUE	= "\x1b[34m"
PURPLE	= "\x1b[35m"
CYAN	= "\x1b[36m"
WHITE	= "\x1b[37m"
