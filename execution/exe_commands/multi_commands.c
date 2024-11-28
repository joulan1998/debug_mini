/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:43:06 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/26 11:43:00 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	multi_util(t_minishell *data, set_args *args, int *fds, int *to_close)
{
	int		fork_res;
	char	*path;

	path = check_acces(data, args->args[0]);
	if (!path)
		return (1);
	fork_res = fork();
	if (fork_res == -1)
		return (perror("forking error"), 1);
	if (fork_res == 0)
	{
		close_fd(to_close);
		if (fds[0] != 0)
			dupping(fds[0], 0);
		// if (args->input != 0)
			// dupping(args->input, 0);
		if (fds[1] != 1)
			dupping(fds[1], 1);
		execve(path, args->args, data->env);
		errno_handling(data, &errno, path);
	}
	free(path); ///another leak
	return (fork_res);
}

void	close_pipes(int	**table_fd, int size)
{
	int	index;
	int	**tmp;

	tmp = table_fd;
	index = size - 1;
	while (index >= 0)
	{
		close((table_fd[index][1]));
		close((table_fd[index][0]));
		index--;
	}
	index = size - 1;
	while (index >= 0)
	{
		free(tmp[index]);
		index--;
	}
	free(tmp);
}

int	multi_helper(t_minishell *data, set_args *args, int i, int **pipes)
{
	int	size;

	size = ft_lstsize_c(data->commands);
	if (i == 0)
		return (multi_util
			(data, args,
				(int []){0, pipes[0][1]}, (int []){pipes[0][0], -1}));
	else if (i == (size -1))
		return (multi_util
			(data, args, (int []){pipes[i - 1][0],
			1}, (int []){pipes[i - 1][1], -1}));
	else
		return (multi_util
			(data, args, (int []){pipes[i - 1][0]
			, pipes[i][1]}, (int []){pipes[i][0], -1}));
}

void	closing(int **pipes, int i, int size)
{
	if (i > 0)
		close (pipes[i -1][0]);
	if (i < size - 1)
		close (pipes[i][1]);
}

int	multi_commands(t_minishell	*data)
{
	set_args	*args;
	int			size;
	int			**pipe_fd;
	int			i;
	pid_t		pid;

	args = data->commands;
	size = ft_lstsize_c(args);
	if (initialize_fds(&pipe_fd, size - 1) == -1)
		return (-1);
	i = 0;
	while (args)
	{
		if ((i < size - 1))
			if (pipe(pipe_fd[i]) != 0)
				return (perror("pipe error"), -1);
		pid = multi_helper(data, args, i, pipe_fd);
		closing(pipe_fd, i, size);
		args = args->next;
		i++;
	}
	if (waitpid_fnc(data, pid) == -1)
		return (-1);
	close_pipes(pipe_fd, size - 1);
	// free_set_args(data->commands);
	return (data->env_lst->exit_status);
}
