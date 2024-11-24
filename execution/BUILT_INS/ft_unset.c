/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:27:22 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/02 13:03:11 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_search(t_minishell *data, char *arg)
{
	t_environ	*local;
	t_environ	*prev;

	local = data->env_lst;
	while (local)
	{
		if (ft_strncmp(local->var, arg, ft_strlen(arg) + 1) == 0)
		{
			free(local->var);
			free(local->value);
			if (prev)
				prev->next = local->next;
			else
				data->env_lst = local->next;
			free (local);
		}
		prev = local;
		local = local->next;
	}
}

int	ft_unset(t_minishell *data)
{
	t_environ	*local;
	int			i;

	i = 0;
	while (++i < count_table_entries(data->commands->args))
	{
		if (check_syntax_for_export (data->commands->args[i]) == 0)
			return (ft_error_export_2_args(data->commands->args[0],
					data->commands->args[i]), 1);
		local = data->env_lst;
		ft_search(data, data->commands->args[i]);
	}
	return (0);
}
