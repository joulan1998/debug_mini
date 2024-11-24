/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:48:34 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/02 15:30:25 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	test_print(t_minishell *data)
{
	t_environ	*local_lst;
	int			i;
	char		**list;

	i = 0;
	local_lst = data->env_lst;
	list = malloc((ft_lstsize(data->env_lst) + 1) * sizeof(char *));
	if (!list)
		return (0);
	while (local_lst)
	{
		if (!ft_strncmp(local_lst->var, "_", 2))
		{
			local_lst = local_lst->next;
			continue ;
		}
		joinning_for_print(&local_lst, &list[i]);
		if (!list[i++])
			return (ft_free_table(&list), -1);
		local_lst = local_lst->next;
	}
	list[i] = NULL;
	sort_and_print(list);
	ft_free_table(&list);
	return (1);
}

int	is_exits(t_minishell *data, char *key)
{
	t_environ	*local;
	char		*local_key;

	local = data->env_lst;
	local_key = extract_key (key);
	if (local_key[ft_strlen (local_key) - 1] == '+')
		local_key[ft_strlen (local_key) - 1] = '\0';
	while (local)
	{
		if (ft_strncmp(local->var, local_key, ft_strlen(local->var) + 1) == 0)
			return (free(local_key), 1);
		local = local->next;
	}
	return (free(local_key), 0);
}

int	ft_append_for_export(t_minishell *data, char *line)
{
	t_environ	*local;
	char		*tmp;
	char		*local_value;
	char		*var;

	local = data->env_lst;
	local_value = extract_value(line);
	var = extract_key(line);
	var[ft_strlen(var) - 1] = '\0';
	while (local)
	{
		if (!ft_strncmp(local->var, var, ft_strlen(var)))
		{
			tmp = local->value;
			local->value = ft_strjoin(local->value, local_value);
			free (tmp);
			free (local_value);
			return (0);
		}
		local = local->next;
	}
	ft_lstadd_back_env (&(data->env_lst), ft_lstnew_env(var, local_value));
	return (-1);
}

int	update_export(t_minishell *data, char **table)
{
	char	*key;
	char	*value;
	int		i;
	int		re;

	i = -1;
	while (table && table[++i])
	{
		if (check_syntax_for_export(table[i]))
		{
			key = extract_key(table[i]);
			value = extract_value(table[i]);
			if (is_exits(data, key) && (ft_strchr(key, '+') != NULL))
				re = ft_append_for_export(data, table[i]);
			else if (is_exits(data, key) && (ft_strchr(key, '+') == NULL))
				re = final_update(data, key, value, false);
			else if (!is_exits(data, key) && (ft_strchr(table[i], '=') != NULL))
				re = final_update(data, key, extract_value(table[i]), true);
			else if ((ft_strchr(table[i], '=') == NULL))
				re = final_update(data, key, extract_value(table[i]), true);
		}
		else
			return (ft_error_export_2_args("export", table[i]), 0);
	}
	return (re);
}

int	ft_export(t_minishell *data)
{
	t_environ	*local;
	char		**args;

	local = (data)->env_lst;
	args = &((data)->commands->args[1]);
	if (!(*args))
		test_print(data);
	else
		update_export(data, args);
	return (0);
}
