/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:48:34 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/28 12:26:15 by ael-garr         ###   ########.fr       */
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
	while (local_lst && local_lst->value && local_lst->var)
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

int	ft_append_for_export(t_minishell *data, char *key,char *value)
{
	t_environ	*local;
	char		*tmp;

	local = data->env_lst;
	if (!value)
	{
		ft_error_export_2_args("export", key);
		free(key);
		return (1);
	}
	key[ft_strlen(key) - 1] = '\0';
	if (!is_exits(data, key))
		return(final_update(data, key, value, true));
	while (local)
	{
		if (!ft_strncmp(local->var, key, ft_strlen(key)))
		{
			tmp = local->value;
			local->value = ft_strjoin(local->value, value);
			return (free(key), free(tmp), free(value), 0);
		}
		local = local->next;
	}
	ft_lstadd_back_env (&(data->env_lst), ft_lstnew_env(key, value));
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
			if (ft_strchr(key, '+') != NULL)
				re = ft_append_for_export(data, key, value);
			else if (is_exits(data, key) && (ft_strchr(key, '+') == NULL))
				re = final_update(data, key, value, false);
			else if (!is_exits(data, key) && (ft_strchr(table[i], '=') != NULL))
				re = final_update(data, key, value, true);
			else if ((ft_strchr(table[i], '=') == NULL))
				re = final_update(data, key, value, true);
		}
		else{
			return (ft_error_export_2_args("export", table[i]), 1);}
	}
	return (re);
}

int	ft_export(t_minishell *data)
{
	int			result;
	char		**args;

	args = &((data)->commands->args[1]);
	if (!(*args))
		result = test_print(data);
	else
		result = update_export(data, args);
	return (result);
}
