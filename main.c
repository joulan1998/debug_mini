/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:46:08 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/26 09:32:13 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void f()
{
	system("leaks minishell");
}

void	initialize_minishell(t_minishell *data, char **env)
{
	data->env = env;
	data->env_lst = create_list(data);
	init_signl(1);
	data->env_lst->exit_status = 0;
}

void	cleanup_and_exit(t_minishell *data)
{
	free(data->line);
	exit(data->env_lst->exit_status);
}

int	process_input(t_minishell *data)
{
	add_history(data->line);
	data->list = parsing(data->line, data->env_lst);
	if (syntax(&data->list) == 1)
	{
		free_t_list(data->list);
		error_message(data->list, data->env_lst);
		return (-1);
	}
	data->list = expanding(data->list, data->env_lst);
	classing(&data->list);
	data->commands = args(&data->list, data->env_lst, pipen(&data->list));
	return (1);
}

void	execute_commands(t_minishell *data)
{
	g_signal = 1;
	data->env_lst->exit_status = exec(data);
	g_signal = 0;
	// free_set_args(data->commands);
	free_t_list(data->list);
	free(data->line);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	data;
	atexit(f);
	(void)argc;
	(void)argv;
	initialize_minishell(&data, env);
	while (1)
	{
		data.line = readline(PROMPT);
		if (!data.line || !ft_strcmp(data.line, "exit"))
			cleanup_and_exit(&data);
		if (data.line[0] == '\0')
		{
			free(data.line);
			continue ;
		}
		if (process_input(&data) == -1)
		{
			free(data.line);
			continue ;
		}
		if (data.list)
			execute_commands(&data);
		// if (data.commands->args)
		// 	ft_free_table(&data.commands->args);
			// free_set_args(data.commands);
	}
}
