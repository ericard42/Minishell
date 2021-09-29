NAME		=	minishell

HEADER		=	./includes/

LIBFT		=	libft/libft.a

CC			=	clang

CFLAGS		=	-Werror -Wall -Wextra -g -I $(HEADER) #-fsanitize=address

SRCS		=	srcs/minishell.c \
				srcs/frame_init.c \
				srcs/lexer_new.c \
				srcs/echo.c \
				srcs/echo_utils.c \
				srcs/exec_utils.c \
				srcs/pwd.c \
				srcs/env.c \
				srcs/export.c \
				srcs/unset.c \
				srcs/find_var_env.c \
				srcs/termcaps.c \
				srcs/lexer_utils.c \
				srcs/input_loop.c \
				srcs/history.c \
				srcs/ft_putchar.c \
				srcs/close.c \
				srcs/errors.c \
				srcs/expension_new.c \
				srcs/space_clear.c \
				srcs/cd.c \
				srcs/cmd_redirector.c \
				srcs/exec.c \
				srcs/chained_pipe.c \
				srcs/pipe.c \
				srcs/redirector.c \
				srcs/ext_code.c \
				srcs/input_utils.c \
				srcs/operators.c \
				srcs/operator_utils.c \
				srcs/operator_utils_two.c \
				srcs/redirector_utils.c \
				srcs/fd_redirector_utils.c \
				srcs/signals.c \
				srcs/exec_utils_two.c \
				srcs/lexer_utils_two.c \
				srcs/lexer_utils_three.c \
				srcs/expension_utils.c \

OBJS		=	$(SRCS:.c=.o)

all			:	$(LIBFT) $(NAME)

$(NAME)		:	$(OBJS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lncurses
				@echo "\\n\033[32;1m MINISHELL COMPLETE \033[0m \\n"

$(LIBFT)	:
				make -C ./libft

clean		:
				rm -rf $(OBJS)
				make clean -C ./libft

fclean		:	clean
				rm $(NAME)
				make fclean -C ./libft

re			:	fclean all
