/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:06:33 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/27 14:54:58 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_minishell *data)
{
	t_environ	*local;

	local = data->env_lst;
	while (local)
	{
		printf("%s=%s\n", local->var, local->value);
		local = local->next;
	}
	return (0);
}

int	joinning_for_print(t_environ **node, char **list)
{
	t_environ	*local;
	char		*temp;
	char		*temp1;

	local = *(node);
	if (!local->value)
		*list = ft_strjoin(local->var, "\0");
	else
	{
		temp = ft_strjoin(local->var, "=\"");
		if (!temp)
			return (-1);
		temp1 = ft_strjoin(local->value, "\"");
		if (!temp1)
			return (-1);
		*list = ft_strjoin(temp, temp1);
		free (temp);
		free (temp1);
	}
	return (0);
}

int	final_update(t_minishell *data, char *key, char *value, bool create)
{
	t_environ	*lst;

	lst = data->env_lst;
	if (!create)
	{
		while (lst)
		{
			if (!ft_strncmp(lst->var, key, (ft_strlen(lst->var) + 1)))
			{
				if (value)
				{
					free (lst->value);
					lst->value = value;
				}
			}
			lst = lst->next;
		}
		return (free(key), 0);
	}
	else
	{
		ft_lstadd_back_env(&data->env_lst, ft_lstnew_env(key, value));
		return(0);
	}
	return (1);
}
