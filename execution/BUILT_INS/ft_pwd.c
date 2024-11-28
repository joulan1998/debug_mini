/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:41:45 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/26 16:39:50 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *name_without_alloc(t_minishell *data, char *name)
{
	t_environ *local;
	local = data->env_lst;
	while (local)
	{
		if (ft_strncmp(local->var, name, ft_strlen(name)))
			return(local->value);
		local = local->next;
	}
	return (NULL);
}
int	ft_pwd(t_minishell	*data)
{
	char	*cwd;
	char *pp;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		pp = ft_find_node(data, "OLDPWD");
		printf("%s\n", pp);
		free(pp);
		return (0);
	}
	else
	{
		printf("%s\n", cwd);
		free(cwd);
		return (0);
	}
	return (0);
}
