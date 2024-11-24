/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   %%%%%%to_linked_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:10:30 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/19 13:08:33 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_environ	*create_list(t_minishell *data)
{
	t_environ	*lst;
	char		**table;
	char		*key_name;
	char		*key_value;
	int			i;

	table = data->env;
	lst = NULL;
	i = 0;
	if (!table || !table[0])
		return (NULL);
	while (table[i])
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
		i++;
	}
	return (lst);
}
