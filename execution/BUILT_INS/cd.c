/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:47:58 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/26 18:06:32 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/param.h>

int	s(t_minishell *data)
{
	t_environ	*local;

	local = data->env_lst;
	while (local)
	{
		if (!ft_strncmp(local->var, "OLDPWD", 6))
		{
			if (ft_strlen(local->value) > 0)
				free(local->value);
			return (1);
		}
		local = local->next;
	}
	return (1);
}

int	set_env(t_minishell *data, char *old, char *new)
{
	t_environ	*local;

	local = data->env_lst;
	while (local)
	{
		if (!ft_strncmp(local->var, old, (ft_strlen (local->var) + 1)))
		{
			if (!ft_strncmp(local->value, "OLDPWD", 7))
			{
				free(local->value);
				local->value = NULL;
			}
			local->value = new;
			return (0);
		}
		local = local->next;
	}
	return (0);
}

int	small_prot(t_minishell *data, char *pwd)
{
	char	*to_free;

	to_free = ft_find_node(data, "PWD");
	set_env(data, "OLDPWD", ft_strjoin(pwd, "/.."));
	free(to_free);
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
		ft_strlcpy(old_pwd, ft_find_node(data, "PWD"), MAXPATHLEN);
	if ((s(data) && small_prot(data, old_pwd)))
		return (ft_putstr_fd("minishell: cd: ", 2), perror(NULL), 1);
	return (0);
}
