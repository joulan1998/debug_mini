/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:29:24 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/25 17:31:29 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	test_flag(char *buffer)
{
	int	flag;

	flag = 0;
	if (buffer && *buffer && *buffer == '-')
	{
		buffer++;
		while (*buffer && (*buffer == 'n' || *buffer == '\\'))
		{
			if (*buffer++ == '\\')
			{
				buffer++;
				continue ;
			}
			flag = 1;
			buffer ++;
		}
		if (flag > 0 && !(*buffer))
			return (true);
	}
	return (false);
}

void	echo_final(char *s,  int fd)
{
	while (*s)
	{
		if (*s == '\\')
		{
			s++;
			continue ;
		}
		ft_putchar_fd(*s, fd);
		s++;
	}
}

int	ft_echo(t_minishell *data)
{
	char	**local;
	int		flag;

	local = &(data->commands->args[1]);
	flag = test_flag(local[0]);
	if (!local || !local)
		return (-1);
	if (flag)
		local++;
	while (local && *local)
	{
		echo_final(*local, data->commands->output);
		ft_putstr_fd(" ", data->commands->output);
		local++;
	}
	if (!flag)
		ft_putstr_fd("\n", data->commands->output);
	return (0);
}
