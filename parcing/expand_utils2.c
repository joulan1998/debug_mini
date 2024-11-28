/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:37:16 by yosabir           #+#    #+#             */
/*   Updated: 2024/11/26 22:34:29 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*process_variable(t_list *current, t_environ *env, int *flag)
{
	if (current->command == VAR && *flag == 0)
		current->content = expand_variable(current, env);
	else if (current->command == HEREDOC)
		*flag = 1;
	return (current);
}

t_list	*process_double_quote(t_list *current, t_environ *env, int flag)
{
	char	*new_content;

	if (flag == 1)
	{
		new_content = ft_strtrim(current->content, "\"");
		free(current->content);
		current->content = new_content;
	}
	else
		current->content = expand_double_q_variable(current, env);
	return (current);
}

t_list	*process_single_quote(t_list *current)
{
	char	*new_content;

	new_content = ft_strtrim(current->content, "'");
	free(current->content);
	current->content = new_content;
	return (current);
}
