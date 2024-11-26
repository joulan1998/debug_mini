/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:47:49 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/26 09:31:53 by ael-garr         ###   ########.fr       */
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

char	*find_path(char	*path, char *ftn)
{
	char	**table;
	char	*res;
	int		i;

	i = 0;
	table = ft_split(path, ':');
	free(path);
	while (i < count_table_entries(table))
	{
		res = ft_strjoin(table[i], "/");
		res = joinning_and_free(res, ftn);
		if (access (res, X_OK) == 0)
		{
			ft_free_table (&table);
			return (res);
		}
		free(res);
		i++;
	}
	ft_free_table(&table);
	return (ft_strdup(ftn));
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
	else
	{
		node_contet = ft_find_node(data, "PATH");
		if (!node_contet)
			return (free_table(data), NULL);   //maybe a shoul not free it
		else
			return (find_path(node_contet, ftn));
		ft_free_table (&table);
	}
	return (ft_strdup(ftn));
}

void	errno_handling(t_minishell *data, int *err, char *path)
{
	if (*err == ENOENT && !ft_strchr(path, '/'))
	{
		ft_error(path, COMMAND_NOT_FOUND);
		free (path);
		exit(127);
	}
	free(path);
	if (*err == EPERM)
	{
		// free(path);
		ft_putstr_fd(PROMPT, 2);
		ft_error(data->commands->args[0], PERM_ERROR);
		exit(126);
	}
	if (*err == EACCES || *err == EFAULT)
	{
		// free (path);
		perror(PROMPT);
		exit(126);
	}
	// free (path);
	perror(PROMPT);
	exit (127);
}

int	exec_smpl_cmnd(t_minishell *data)
{
	char	*path;
	int		fork_res;

	// printf("args0 %s\n",data->commands->args[0]);
	// printf("input %d\n",data->commands->input);
	if (!data->commands->args || 
		((data->commands->input == -1)/* && (data->commands->args[0])*/))
	{
		if (data->commands->input == -1)
			ft_error(data->commands->args[1], NOSUCHFORD);
		return -1;
	}
	path = check_acces (data, data->commands->args[0]);
	fork_res = fork();
	if (fork_res == -1)
		return (perror (PROMPT), -1);
	if (fork_res == 0)
	{
		if (data->commands->input != 0)
			dup2(data->commands->input, 0);
		if (data->commands->output)
			dup2(data->commands->output, 1);
		printf(">>>>DSDSD:%p\n",&data->commands->output);
		execve(path, data->commands->args, (data->env));
		free(path);
		errno_handling(data, &errno, path);
	}
	// exit(9);
	free (path);
		// exit(9);
	if (waitpid_fnc(data, fork_res) == -1)
		return (-1);
	return (data->env_lst->exit_status);
}








// i should fix the simple command all cases