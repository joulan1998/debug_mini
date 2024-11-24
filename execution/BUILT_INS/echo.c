/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:29:24 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/22 22:53:00 by yosabir          ###   ########.fr       */
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

void	echo_final(char *s)
{
	while (*s)
	{
		if (*s == '\\')
		{
			s++;
			continue ;
		}
		ft_putchar_fd(*s, 1);
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
		echo_final(*local);
		ft_putstr_fd(" ", 1);
		local++;
	}
	if (!flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
