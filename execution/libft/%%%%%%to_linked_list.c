/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   %%%%%%to_linked_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:10:30 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/28 16:59:00 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void 	add_own_path(t_environ **lst)
{
	int flag = 0;
	t_environ *local;
	local = *lst;
	while (local)
	{
		if (!ft_strncmp(local->var, "PATH", 5))
		{
			flag = 1;
			break;
		}
		local = local->next;
	}
	if (!flag || ft_lstsize(*lst) == 0)
		ft_lstadd_back_env(lst, ft_lstnew_env(ft_strdup("PATH"), ft_strdup(OWN_PATH)));
}

t_environ	*create_list(t_minishell *data)
{
	t_environ	*lst;
	char		**table;
	char		*key_name;
	char		*key_value;
	int			i;

	table = data->env;
	lst = NULL;
	i = -1;
	// if (!count_table_entries(table))
	// 	ft_lstadd_back_env(&lst,
	// 		ft_lstnew_env(ft_strdup("PATH"), ft_strdup(OWN_PATH)));
	while (table[++i] && table)
	{
		key_name = extract_key(table[i]);
		key_value = extract_value(table[i]);
		if (!key_name || !key_value)
		{
			free(key_name);
			free(key_value);
			return (NULL);
		}
		ft_lstadd_back_env(&lst, ft_lstnew_env(key_name, key_value));
	}
	add_own_path(&lst);
	return (lst);
}
