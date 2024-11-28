/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:27:22 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/28 16:51:27 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_search(t_minishell *data, char *arg)
{
	t_environ	*local;
	t_environ	*prev;
	t_environ	*next;

	local = data->env_lst;
	prev = NULL;

	if (!ft_strncmp(arg, "PATH",5) && ft_lstsize(local) ==1)
		local = NULL;
	while (local)
	{
		next = local->next; // Store the next node to continue traversal after deletion
		if (local->value && local->var){

			if (!ft_strncmp(local->var, arg, ft_strlen(arg) + 1))
			{
				free(local->var);// local->var = NULL;
				free(local->value);// local->value = NULL;
				if (prev)
					prev->next = next; // Skip the deleted node
				else
					data->env_lst = next; // Update head if the head is being deleted
				free(local);
				local = NULL;
			}
		}
		prev = local;
		local = next; // Move to the next node
	}
}
// void	ft_search(t_minishell *data, char *arg)
// {
// 	t_environ	*local;
// 	t_environ	*prev;

// 	printf("list size %d\n",ft_lstsize(data->env_lst));
// 	local = data->env_lst;
// 	while (local)
// 	{
// 		if (local->next && (!ft_strncmp(local->var, arg, ft_strlen(arg) + 1)))
// 		{
// 			free(local->var);
// 			free(local->value);
// 			if (prev)
// 				prev->next = local->next;
// 			else
// 				data->env_lst = local->next;
// 			free (local);
// 		}
// 		prev = local;
// 		if (local->next)
// 			local = local->next;
// 	}
// }

int	ft_unset(t_minishell *data)
{
	// t_environ	*local;
	int			i;

	i = 1;
	// free(data->env_lst->value);
	// free(data->env_lst->var);
	
	// free(data->env_lst);
	// data->env_lst = NULL;
	while (i < count_table_entries(data->commands->args))
	{
		if (check_syntax_for_export (data->commands->args[i]) == 0)
			return (ft_error_export_2_args(data->commands->args[0],
					data->commands->args[i]), 1);
		// local = data->env_lst;
		ft_search(data, data->commands->args[i]);
		i++;
	}
	return (0);
}
