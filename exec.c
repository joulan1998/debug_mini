/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:05:32 by yosabir           #+#    #+#             */
/*   Updated: 2024/11/24 20:22:02 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	exec(t_minishell *data)
{
	int result;
	
	result = 0;
	if (data->list->type == BUILT_IN && ft_lstsize_c(data->commands) == 1)
		result = start_execution(data);
	else if (ft_lstsize_c(data->commands) == 1  && data->list->type == SIMPLE_COMMAND)
		result = exec_smpl_cmnd(data);
	else if (ft_lstsize_c(data->commands) >= 2)
	{
		result = multi_commands(data);
		exit(19);
	}
	// ft_free_table(&data->commands);
	// ft_free_table(&data->args);
	// if (result == -1)
		// return(ft_err_msg((t_error){COMMAND_NOT_FOUND,ENO_CMMND_NT_FOND,data->args[0]}), -1);
	return (result);
}

int	start_execution(t_minishell *data)
{
	// puts("ddjksjdjks");
	// int result;
	// if (!data->list)
	// 	return (-1);
	if (!ft_strncmp(data->list->content,"cd",3))
		data->env_lst->exit_status = ft_cd(data);
	else if (!ft_strncmp(data->list->content,"pwd",4))
		data->env_lst->exit_status = ft_pwd(data);
	else if (!ft_strncmp(data->list->content, "echo", 5))
		ft_echo(data);
	else if (!ft_strncmp(data->list->content, "export", 7))	
		ft_export(data);
	else if (!ft_strncmp(data->list->content, "env", 4))
		ft_env(data);
	else if (!ft_strncmp(data->list->content, "exit", 5))
		ft_exit(data);
	else if (!ft_strncmp(data->list->content, "unset", 6))
		ft_unset(data);
	// ft_free_table(&data->commands->args);
	// free_list(data->list);
	// else 
	// 	ft_err_msg((t_error){COMMAND_NOT_FOUND,ENO_CMMND_NT_FOND,data->args[0]});
	return (data->env_lst->exit_status); // it was -1 edited by yosabir
	// free(data->old_path);
}