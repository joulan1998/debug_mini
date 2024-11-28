/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:47:49 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/28 17:09:50 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	waitpid_fnc(t_minishell *data, int pid)
{
	pid_t	wait;
	int		status;

	if (pid == -1)
		wait = waitpid(-1, &status, 0);
	else
		wait = waitpid(pid, &status, 0);
	if (wait == -1)
		return (wait);
	if (WIFEXITED(status) || status == ENOEXEC)
		data->env_lst->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->env_lst->exit_status = WTERMSIG(status) + 128;
	return (0);
}

void free_path_close_fd(char *path,t_minishell *data)
{
	if (path)
		free(path);
	if (data->commands->input > 2)
		close(data->commands->input);
	if (data->commands->output > 2)
		close(data->commands->output);
}

char	*check_acces(t_minishell *data, char *ftn)
{
	char	**table;
	int		i;
	char	*node_contet;

	table = NULL;
	i = 0;
	if (!ftn || !data->env_lst)
		return (NULL);
	if (access (ftn, X_OK) == 0)
		return (ft_strdup(ftn));
	else if (data->env_lst)
	{
		node_contet = ft_find_node(data, "PATH");
		if (!node_contet)
			return (free_set_args(data->commands), NULL);   //maybe a shoul not free it
			// return (ft_strdup(OWN_PATH), NULL);   //maybe a shoul not free it
		else
			return (find_path(node_contet, ftn));
		ft_free_table (&table);
	}
	return (ft_strdup(ftn));
}

void	errno_handling(t_minishell *data, int *err, char *path)
{
	close(data->commands->output);
	close(data->commands->input);
	if (*err == ENOENT && !ft_strchr(path, '/'))
	{
		ft_error(path, COMMAND_NOT_FOUND);
		free (path);
		exit(127);
	}
	free(path);
	if (*err == EPERM)
	{
		ft_putstr_fd(PROMPT, 2);
		ft_error(data->commands->args[0], PERM_ERROR);
		exit(126);
	}
	if (*err == EACCES || *err == EFAULT)
	{
		perror(PROMPT);
		exit(126);
	}
	perror(PROMPT);
	exit (127);
}

int	exec_smpl_cmnd(t_minishell *data)
{
	char	*path;
	int		fork_res;

	path = check_acces (data, data->commands->args[0]);
	if (!data->commands->args || 
		((data->commands->output == -1)/* && (data->commands->args[0])*/))
	{
		if (data->commands->output == -1 || !path)
			ft_error(data->commands->args[1], NOSUCHFORD);
		return -1;
	}
	fork_res = fork();
	if (fork_res == -1)
		return (perror (PROMPT), -1);
	if (fork_res == 0)
	{
		if (data->commands->input != 0)
			dup2(data->commands->input, 0);
		if (data->commands->output != 1)
			dup2(data->commands->output, 1);
		if(path)	
			execve(path, data->commands->args, (data->env));
		// free(path);
		errno_handling(data, &errno, path);
	}
	free_path_close_fd(path, data);
	if (waitpid_fnc(data, fork_res) == -1)
		return (-1);
	return (data->env_lst->exit_status);
}








// i should fix the simple command all cases