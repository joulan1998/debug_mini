/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:15:29 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/21 15:44:55 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_number(char *str)
{
	char *local;
	
	if(!str)
		return(0);
	local = str;
	while (*local)
	{
		if (*local == ' ' || *local == '-' || (*local >= '0' && *local <= '9'))
			local++;
		else
			return (0);
	}
	return(1);
}

void free_env(t_minishell *data)
{
	t_environ *local;
	t_environ *tmp;

	local = data->env_lst;
	tmp = local;
	while (local)
	{
		tmp = tmp->next;
		free(local->value);
		free(local->var);
		free(local);
		local = tmp;
		// tmp = tmp->next;
	}
	free(local);
}

int free_table(t_minishell *data)
{
	char **local;
	char *tmp;
	local = data->commands->args;
	tmp = *local;
	while (tmp)
	{
		if (tmp)
		{
			local++;
			free(tmp);
			tmp = *local;
		}
		free(data->commands->args);
	}
	return(0);

}

int garbage_collector(t_minishell *data)
{
	// (void)data;
	// t_environ *list;
	// t_environ *tmp;
	
	free_table(data);
	free(data->line);
	free_env(data);
	// // free(data->env_lst);
	// list = data->env_lst;
	// tmp = list;
	// if (tmp)
	// {
	// 	while (tmp)
	// 	{
	// 		list++;
	// 		if(tmp)
	// 			free(tmp);
	// 		else{
	// 			list = list->next;
	// 			tmp = list;
	// 		}
	// 		tmp = list;
	// 		list = list->next;
	// 	}
	// }
	return(0);
	

}

// static bool	ft_isnumber(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (!ft_isdigit(s[i]))
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }

static void	ft_skip_spaces_and_get_sign(char *s, int *i, int *sign)
{
	while (s[*i] && s[*i] == ' ')
		(*i)++;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
}

int	ft_exittoi(char *s)
{
	int					i;
	int					sign;
	int					exit_s;
	unsigned long long	result;

	i = 0;
	sign = 1;
	ft_skip_spaces_and_get_sign(s, &i, &sign);
	if (!is_number(s + i))
	{
		exit_s = ft_err_msg((t_error){NUMRC_ARG_REQUIRED, ENO_EXEC_255, s});
		exit(exit_s);
		// (ft_clean_ms(), exit(exit_s));
	}
	result = 0;
	while (s[i])
	{
		result = (result * 10) + (s[i] - '0');
		if (result > 9223372036854775807)
		{
			exit_s = ft_err_msg((t_error){NUMRC_ARG_REQUIRED, ENO_EXEC_255, s});
			exit(exit_s);
			// (ft_clean_ms(), exit(exit_s));
		}
		i++;
	}
	return ((result * sign) % 256);
}
void	free_list(t_list	*lst)
{
	t_list	*local;

	local = lst;
	while (local)
		free(local->content);
	local = local->next;

}
void	free_args(set_args *args)
{
	set_args	*local;
	
	local = args;
	while (local)
		ft_free_table(&local->args);
	local = local->next;
}

int ft_exit(t_minishell *data)
{
	// int exit_s;
	// char *local;
	// free_list(data->list);
	// free_args(data->commands);
	free_env(data);
	// local = data->commands->args[1];
	// exit_s = data->exit_s;
	// if(data->commands->args[1])
	// {
	// 	if (is_number(data->commands->args[1]) && data->commands->args[2])
	// 		ft_err_msg((t_error){TOO_MANY_ARGS ,ENO_TOO_MANY_ARGS,NULL});
	// 	else
	// 		exit_s = ft_exittoi(data->commands->args[1]);
	// }
	// // ft_free_table(&data->args);
	// garbage_collector(data);
	// exit(exit_s);
	// (void)data;
	// c_collector(data);
	exit(data->env_lst->exit_status);
}