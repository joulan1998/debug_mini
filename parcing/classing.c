/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:55:45 by yosabir           #+#    #+#             */
/*   Updated: 2024/11/19 11:28:59 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	checking_command(t_list *token)
{
	return (token && (ft_strcmp(token->content, "echo") == 0
			|| ft_strcmp(token->content, "cd") == 0
			|| ft_strcmp(token->content, "pwd") == 0
			|| ft_strcmp(token->content, "export") == 0
			|| ft_strcmp(token->content, "unset") == 0
			|| ft_strcmp(token->content, "env") == 0
			|| ft_strcmp(token->content, "exit") == 0));
}

void	classing(t_list **lst)
{
	t_list	*current;

	current = *lst;
	while (current)
	{
		if (checking_command(current))
			current->type = BUILT_IN;
		else
			current->type = SIMPLE_COMMAND;
		current = current->next;
	}
}

int	add_node_to_list(t_list **lst, char *substring, int cmd)
{
	t_list	*new_node;

	new_node = ft_lstnew(substring);
	if (!substring || !new_node)
		return (free(substring), -1);
	new_node->command = cmd;
	ft_lstadd_back(lst, new_node);
	return (0);
}
