NAME	= minishell

#==========================================
# exec
EXEC	= minishell_exec
# parse
PARSE	= minishell_parse
#==========================================

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

# exec src files
EXEC_SRCS =	exec_main.c\

# parse src files
PARSE_SRCS =	parse_main.c\
				./parse/init_env.c \


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
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	: $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft
	@echo $(GREEN) "⚡︎	[ minishell ]	Ready to run minishell" $(RESET)

#====================================#
# make for exec
$(EXEC) : $(EXEC_OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) -o $(EXEC) $(EXEC_OBJS) -L$(LIBFT_DIR) -lft -lreadline
	@echo $(GREEN) "⚡︎	[ minishell_exec ]	Ready to run minishell_exec" $(RESET)

# make for parse
$(PARSE) : $(PARSE_OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) -o $(PARSE) $(PARSE_OBJS) -L$(LIBFT_DIR) -lft -lreadline
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
