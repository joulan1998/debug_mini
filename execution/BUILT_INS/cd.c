/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:47:58 by ael-garr          #+#    #+#             */
/*   Updated: 2024/10/26 14:57:33 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/param.h>

int	set_env(t_minishell *data, char *old, char *new)
{
	t_environ	*local;

	local = data->env_lst;
	while (local)
	{
		if (!ft_strncmp(local->var, old, (ft_strlen (local->var) + 1)))
		{
			local->value = new;
			return (0);
		}
		local = local->next;
	}
	return (0);
}

int	ft_cd(t_minishell *data)
{
	char	old_pwd[MAXPATHLEN];
	char	new_pwd[MAXPATHLEN];
	char	*dst;

	if (!(data->commands->args[1]) && !getenv("HOME"))
		return (1);
	if (!data->commands->args[1])
		dst = getenv("HOME");
	else
		dst = data->commands->args[1];
	old_pwd[0] = '\0';
	getcwd(old_pwd, MAXPATHLEN);
	if (chdir(dst))
		return (ft_putstr_fd("minishell: cd: ", 2), ft_putstr_fd(dst, 2),
			perror(" "), 1);
	if (!getcwd(new_pwd, MAXPATHLEN))
		return (ft_putstr_fd("minishell: cd: ", 2),
			ft_putstr_fd("error retieving current directory: ", 2),
			ft_putstr_fd("getcwd: cannot access parent directories: ", 2),
			perror(NULL), 1);
	if (!ft_strlen(old_pwd) && getenv("PWD"))
		ft_strlcpy(old_pwd, getenv("PWD"), MAXPATHLEN);
	if ((set_env(data, "OLDPWD", old_pwd)) || (set_env(data, "PWD", new_pwd)))
		return (ft_putstr_fd("minishell: cd: ", 2), perror(NULL), 1);
	return (0);
}
