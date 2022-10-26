SRCS		=	exec/export.c \
				exec/utils_parse_home.c \
				exec/signals.c \
				exec/unsetenv.c \
				exec/ft_unset_utils.c \
				exec/cd.c \
				exec/echo.c \
				exec/ft_builtin.c	\
				exec.c \
				exec_chart2.c	\
				exec_fd.c \
				exec_fd_chart2.c \
                exec_fork.c \
				ft_export_utils.c	\
				ft_export_check.c	\
				ft_parser.c \
				readline.c	\
				ft_iterators_token.c	\
				ft_command.c	\
				ft_check_syntax_for_comm.c\
				ft_env.c 	\
				ft_env_utils.c	\
				ft_list_utils_env.c \
				ft_utils.c	\
				ft_utils2.c	\
				ft_check_syntax.c	\
				ft_init.c	\
				ft_parse_dquote.c	\
				ft_parse_dollar.c	\
				ft_dollar_in_quote.c	\
				ft_parse_dollar_utils.c	\
				ft_printer.c	\
				ft_token_utils.c	\
				ft_token_redir_utils.c	\
				ft_token.c	\
				ft_free.c	\
                creat_and_read_files.c \
                cycle_readline.c \
				TEST.c


OBJS		=	$(SRCS:.c=.o)

LBFTDR		=	libft

CC			=	gcc

NAME    	=   minishell

RM			= 	rm -f

#Чтобы работал rl_replace_line
FL_TERM		=	 -L/Users/$(USER)/.brew/Cellar/readline/8.1/lib/ -I/Users/$(USER)/.brew/Cellar/readline/8.1/include

#FL_TERM		=	-L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include ###Для того, чтобы дома работало

FL_RDLN		=	-lreadline

%.o:%.c
				gcc -c -g $< -o $@
				#gcc  -Wall -Wextra -Werror -c $< -o $@

$(NAME):		$(OBJS) $(LBFTDR)
				make bonus -C $(LBFTDR)
				$(CC) $(OBJS) $(LBFTDR)/libft.a $(FL_TERM) $(FL_RDLN) -o $(NAME)

debug:			$(OBJS) $(LBFTDR)
				make bonus -C $(LBFTDR)
				$(CC) -g $(OBJS) $(LBFTDR)/libft.a $(FL_TERM) $(FL_RDLN) -o $(NAME)

all:			$(NAME)

clean:
				$(RM) $(OBJS)
				make clean -C $(LBFTDR)

fclean:			clean
				$(RM) $(NAME)
				make fclean -C $(LBFTDR)

re:				fclean all

.PHONY: 		all clean mlx fclean re