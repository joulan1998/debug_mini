/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_collector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:42:17 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/24 18:21:51 by ael-garr         ###   ########.fr       */
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

	while (list)
	{
		if (list->args)
		{
			temp = list->next;
			i = 0;
			while (list->args[i])
			{
				printf("leaks i think >>>> %p\n", &list->args[i]);
				free(list->args[i]);
				list->args[i] = NULL;
				// free((void *)list->input);
				// free((void *)list->output);
				i++;
			}
			// if (list->args)
			// 	free(list->args);
			printf("leaks i args >>>> %p\n", &list->args);
			printf("leaks %d input >>>> %p\n",i, &list->input);
			printf("leaks %d output >>>> %p\n",i,  &list->output);
			printf("leaks i next >>>> %p\n", &list->next);
			free(list->args);
			// free(list);
		}
		list = temp;
		// list = list->next;
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
