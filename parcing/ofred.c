/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ofred.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:25:28 by yosabir           #+#    #+#             */
/*   Updated: 2024/11/25 17:19:30 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipen(t_list **lst)
{
	t_list	*current;
	int		i;

	current = *lst;
	i = 0;
	while (current)
	{
		if (current->command == PIPE)
			i++;
		current = current->next;
	}
	return (i + 1);
}

t_list	*skip_spaces(t_list *token)
{
	while (token && token->command == SPACEE)
		token = token->next;
	return (token);
}

static int	open_file(t_list *token, t_list *current)
{
	int		i;

	i = 1;
	if (token->command == RD_OUT)
		i = open(current->content, O_CREAT | O_RDWR | O_TRUNC, 0666);
	else if (token->command == APPEND)
		i = open(current->content, O_CREAT | O_RDWR | O_APPEND, 0666);
	return (i);
}

void	handle_red(t_list *token, set_args *cmd_args, t_environ *env)
{
	t_list	*cur;

	cur = token;
	if (token->command == RD_OUT || token->command == APPEND)
	{
		if (cmd_args->output != 1)
			cmd_args->output = close(cmd_args->output);
		cur = skip_spaces(token->next);
		if (!cur)
			return ;
		cmd_args->output = open_file(token, cur);
	}
	else if (token->command == RD_IN || token->command == HEREDOC)
	{
		cur = skip_spaces(token->next);
		if (!cur)
			return ;
		if (token && token->command == RD_IN)
			cmd_args->input = open(cur->content, O_RDONLY);
		else if (token && token->command == HEREDOC)
			cmd_args->input = herdoc(cmd_args->input, cur->content, cur, env);
	}
}
