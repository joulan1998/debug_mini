/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:20:17 by yosabir           #+#    #+#             */
/*   Updated: 2024/11/19 11:54:53 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_redirection(t_list *token)
{
	return (token && (ft_strcmp(token->content, ">>") == 0
			|| ft_strcmp(token->content, "<<") == 0
			|| ft_strcmp(token->content, ">") == 0
			|| ft_strcmp(token->content, "<") == 0));
}

int	is_valid_next(t_list *token)
{
	return (token && (token->command == S_QUOTE
			||token->command == D_QUOTE
			|| token->command == WORD
			|| token->command == VAR));
}

int	syntax_redpipe(t_list **lst)
{
	t_list	*current;

	current = *lst;
	if (!lst || !current)
		return (1);
	if (current && ft_strcmp(current->content, "|") == 0)
		return (1);
	while (current)
	{
		if (is_redirection(current))
		{
			if (check_redirection_followed_by_pipe(current))
				return (1);
		}
		else if (ft_strcmp(current->content, "|") == 0)
		{
			if (check_consecutive_pipes(current))
				return (1);
		}
		current = current->next;
	}
	return (0);
}

int	syntax_consecutive_redirection(t_list **lst)
{
	t_list	*current;
	t_list	*next_token;

	current = *lst;
	if (!lst || !current)
		return (1);
	while (current)
	{
		if (is_redirection(current))
		{
			next_token = current->next;
			while (next_token && is_space(next_token))
				next_token = next_token->next;
			if (next_token && is_redirection(next_token))
				return (1);
		}
		current = current->next;
	}
	return (0);
}

int	syntax_end_of_command(t_list **lst)
{
	t_list	*current;
	t_list	*next_token;

	current = *lst;
	if (!lst || !current)
		return (1);
	while (current)
	{
		if (is_redirection(current) || ft_strcmp(current->content, "|") == 0)
		{
			next_token = current->next;
			while (next_token && is_space(next_token))
				next_token = next_token->next;
			if (!next_token)
				return (1);
			if (!is_valid_next(next_token))
				return (1);
		}
		current = current->next;
	}
	return (0);
}
