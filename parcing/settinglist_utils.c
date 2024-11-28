/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settinglist_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:47:19 by yosabir           #+#    #+#             */
/*   Updated: 2024/11/28 13:58:26 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**split_trimmed(char *str)
{
	char	*trimmed;
	char	**split_result;

	trimmed = ft_strtrim(str, " \t");
	if (!trimmed)
		return (NULL);
	split_result = ft_split(trimmed, ' ');
	return (split_result);
}

void	list_variable(t_list **current, set_args *cmd_args)
{
	char	**split_parts;
	int		i;

	split_parts = split_trimmed((*current)->content);
	if (!split_parts)
		return ;
	i = 0;
	while (split_parts[i])
	{
		add_arg_to_set_args(cmd_args, split_parts[i]);
		free(split_parts[i]);
		i++;
	}
	free (split_parts);
}

void	process_argument(t_list **current, set_args *cmd_args)
{
	char	*arg_content;

	if ((*current)->command == VAR)
		list_variable(current, cmd_args);
	else
	{
		arg_content = concatenate_args(current);
		if (!arg_content)
			arg_content = ft_strdup("");
		add_arg_to_set_args(cmd_args, arg_content);
		free(arg_content);
	}
}

char	*concatenate_args(t_list **current)
{
	char	*arg_content;
	char	*temp;

	arg_content = ft_strdup((*current)->content);
	if (!arg_content)
		return (NULL);
	while ((*current)->next
		&& ((*current)->next->command == WORD
			|| (*current)->next->command == S_QUOTE
			|| (*current)->next->command == D_QUOTE
			|| (*current)->next->command == VAR))
	{
		temp = ft_strjoin(arg_content, (*current)->next->content);
		free(arg_content);
		arg_content = temp;
		*current = (*current)->next;
	}
	return (arg_content);
}
