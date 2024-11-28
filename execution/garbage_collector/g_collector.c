/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_collector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:42:17 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/28 13:31:35 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_commands(set_args *list)
{
	while (list)
	{
		ft_free_table(&list->args);
		list = list->next;
	}
}

void	free_environment(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	free_set_args(set_args *list)
{
	set_args	*temp;
	int			i;
	if(!list || !list->args)
		return ;

	while (list)
	{
		if (list->args/*  && list->args[0]*/)
		{
			temp = list->next;
			i = 0;
			while (list->args && list->args[i])
			{
				free(list->args[i]);
				list->args[i] = NULL;
				i++;
			}
			// free(list->args);
		}
		list = temp;
	}
}

void	free_t_list(t_list *list)
{
	t_list	*lst;
	t_list	*temp;

	if (!list)
		return ;
	lst = list;
	while (lst)
	{
		free(lst->content);
		temp = lst;
		lst = lst->next;
		free(temp);
	}
}

void	clear_env_list(t_environ *env_lst)
{
	t_environ	*temp;

	while (env_lst)
	{
		temp = env_lst;
		env_lst = env_lst->next;
		free(temp->var);
		free(temp->value);
		free(temp);
	}
}

void	c_collector(t_minishell *data)
{
	if (data->commands)
	{
		free_set_args(data->commands);
		data->commands = NULL;
	}
	if (data->list)
	{
		free_t_list(data->list);
		data->list = NULL;
	}
	if (data->env_lst)
	{
		free_environment(data->env);
		data->env_lst = NULL;
	}
}
