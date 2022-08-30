# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/08 16:56:28 by aamajane          #+#    #+#              #
#    Updated: 2022/06/14 11:19:18 by aamajane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

LIBMS	=	srcs/libms.a

LIBFT	=	libft/libft.a

SRCS	=	srcs/main.c \
			srcs/parsing/parsing.c \
			srcs/parsing/check_quotes_syntax.c \
			srcs/parsing/check_pipes_syntax.c \
			srcs/parsing/check_redirections_syntax.c \
			srcs/parsing/join_command_line.c \
			srcs/parsing/split_command_line.c \
			srcs/parsing/add_spaces.c \
			srcs/parsing/split_commands.c \
			srcs/expanding/expanding.c \
			srcs/expanding/expand_and_remove_quotes.c \
			srcs/expanding/expand_variable.c \
			srcs/expanding/expand_heredoc_variable.c \
			srcs/execution/execution.c \
			srcs/execution/child_process.c \
			srcs/execution/get_commands_infos.c \
			srcs/execution/get_command_read_fd.c \
			srcs/execution/get_command_write_fd.c \
			srcs/execution/get_command_arguments.c \
			srcs/execution/get_command_path.c \
			srcs/execution/get_command_pipe_fd.c \
			srcs/builtins/builtin_execution.c \
			srcs/builtins/echo.c \
			srcs/builtins/cd.c \
			srcs/builtins/pwd.c \
			srcs/builtins/export.c \
			srcs/builtins/export_utils.c \
			srcs/builtins/unset.c \
			srcs/builtins/env.c \
			srcs/builtins/exit.c \
			srcs/signals/signals.c \
			srcs/error/error_1.c \
			srcs/error/error_2.c \
			srcs/free/free.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

RDLINE	=	-lreadline -L /Users/aamajane/.brew/opt/readline/lib

LIB		=	ar -rcs

RM		=	rm -rf


all:		$(NAME)

$(NAME):	$(LIBMS) $(LIBFT)
			@$(CC) $(CFLAGS) $(RDLINE) $(LIBMS) $(LIBFT) -o $(NAME)

$(LIBMS):	$(OBJS)
			@$(LIB) $(LIBMS) $(OBJS)

$(LIBFT):
			@cd libft && make

.c.o:
			@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
			@$(RM) $(OBJS) $(LIBMS) $(LIBFT)
			@cd libft && make clean

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
