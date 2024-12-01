/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdocfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:11:29 by yosabir           #+#    #+#             */
/*   Updated: 2024/11/26 21:30:43 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	write_heredoc(t_hdc info, char *result, char *line)
{
	write(info.input, result, ft_strlen(result));
	write(info.input, "\n", 1);
	free(result);
	(void)line;
}

t_hdc	open_create_herdoc_file(int i)
{
	int		fd;
	char	*heredoc_name;
	char	*num;
	char	*dup;
	t_hdc	info;

	dup = ft_strdup("/tmp/heredoc");
	while (1)
	{
		num = ft_itoa(i);
		heredoc_name = ft_strjoin(dup, num);
		free(num);
		if (access(heredoc_name, F_OK) == -1)
			break ;
		i++;
		free(heredoc_name);
	}
	fd = open(heredoc_name, O_CREAT | O_RDWR | O_APPEND, 0666);
	info.file_name = heredoc_name;
	info.input = fd;
	free(dup);
	return (info);
}

static int	handle_tty_error(t_hdc info)
{
	int	fd;

	(1) && (fd = open(ttyname(2), O_RDONLY), dup2(0, fd));
	free(info.file_name);
	return (info.input);
}

int	herdoc(int input, char *del, t_list *token, t_environ *env)
{
	char	*line;
	char	*result;
	int		dont_expand;
	t_hdc	info;

	dont_expand = (token->command == D_QUOTE || token->command == WORD
			|| token->command == VAR);
	info = open_create_herdoc_file(1);
	g_signal = 1;
	while (1)
	{
		line = readline("> ");
		if (!ttyname(0))
			return (handle_tty_error(info));
		if (!line || ft_strcmp(line, del) == 0)
			break ;
		result = expand_here_doc(line, dont_expand, env);
		write_heredoc(info, result, line);
	}
	close(info.input);
	input = open(info.file_name, O_RDONLY);
	return (free(info.file_name), free(line), input);
}
