/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:41:45 by ael-garr          #+#    #+#             */
/*   Updated: 2024/10/26 14:57:58 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_minishell	*data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (printf("%s\n", data->old_path), 0);
	else
	{
		printf("%s\n", cwd);
		free(cwd);
		return (0);
	}
	return (0);
}
