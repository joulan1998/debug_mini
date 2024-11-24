# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 03:45:54 by ael-garr          #+#    #+#              #
#    Updated: 2024/11/24 18:13:55 by ael-garr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXECUTION_SRC = main.c\
				execution/libft/ft_sort_params.c execution/libft/ft_strjoin.c execution/libft/ft_strncmp.c execution/libft/ft_isdigit.c execution/libft/ft_split.c execution/libft/ft_putstr_fd.c execution/libft/ft_isalpha.c execution/libft/ft_strlen.c execution/libft/ft_strdup.c execution/libft/ft_strchr.c execution/libft/ft_lstsize_bonus.c execution/libft/ft_lstadd_back_bonus.c execution/libft/ft_strlcpy.c execution/libft/ft_lstnew_bonus.c execution/libft/%%%%%%to_linked_list.c\
				execution/libft/ft_itoa.c execution/libft/ft_putchar_fd.c execution/libft/ft_strtrim.c execution/libft/ft_substr.c execution/libft/lst.c\
				execution/BUILT_INS/ft_pwd.c execution/BUILT_INS/cd.c execution/BUILT_INS/ft_export.c execution/BUILT_INS/echo.c execution/BUILT_INS/ft_exit.c execution/BUILT_INS/env.c execution/BUILT_INS/ft_export_utils.c execution/BUILT_INS/ft_unset.c\
				execution/errors/error_export.c execution/errors/error_export_2_args.c\
				execution/init_signals.c\
				execution/exe/exec_simple_command.c\
				execution/utils/ft_find_node.c execution/utils/ft_free_table.c execution/utils/joinning_and_free.c\
				execution/exe_commands/multi_commands.c execution/exe_commands/multi_utils.c\
				execution/utils/for_merging.c\
				execution/signals/init_signals.c\
				execution/garbage_collector/g_collector.c exec.c
PARCING_SRC = parcing/classing.c  parcing/helper.c parcing/expand.c parcing/expand_utils.c parcing/herdocfile.c\
              parcing/ofred.c parcing/parsing.c parcing/parsing_word_space.c parcing/settinglist.c parcing/syntax1.c parcing/syntax2.c\
			  parcing/settinglist_utils.c  parcing/parsing_variable.c
BASIC_SRC = $(EXECUTION_SRC) $(PARCING_SRC)

OBJ = ${BASIC_SRC:.c=.o}
CFLAG = -Wall -Wextra -Werror -g  #-fsanitize=address
NAME = minishell
READLINE_L = $(shell brew --prefix readline)/lib
READLINE_I = $(shell brew --prefix readline)/include
CC = cc

all : ${NAME}

$(NAME): $(OBJ) 
		${CC} ${CFLAG} ${OBJ} -L ${READLINE_L} -o ${NAME} -lreadline


%.o: %.c includes/minishell.h
		@${CC} ${CFLAG} -I ${READLINE_I} -c $< -o $@

norm :
	@norminette

clean :
	@rm -rf ${OBJ}

fclean : clean
	@rm -rf ${NAME}

re : fclean all

.PHONY : clean norm
