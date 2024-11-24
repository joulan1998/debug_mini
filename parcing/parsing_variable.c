/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:39:27 by yosabir           #+#    #+#             */
/*   Updated: 2024/11/21 18:41:18 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_special_char(char *str, int k, t_list **lst)
{
	char	*substring;

	substring = ft_substr(str, k, 1);
	if (!substring || add_node_to_list(lst, substring, WORD) == -1)
		return (-1);
	return (k);
}

static int	handle_exit_status(char *str, int i, t_list **lst, t_environ *env)
{
	int		k;
	char	*status;
	char	*substring;
	char	*result;

	k = i++;
	status = ft_itoa(env->exit_status);
	while (str[i] && !is_special_char(str[i]))
		i++;
	substring = ft_substr(str, k + 1, --i - k + 1);
	result = ft_strjoin(status, substring);
	free(status);
	free(substring);
	if (!result || add_node_to_list(lst, result, WORD) == -1)
		return (-1);
	return (i);
}

static int	handle_variable(char *str, int k, int i, t_list **lst)
{
	char	*substring;

	while (str[i] && !is_special_char(str[i]))
		i++;
	substring = ft_substr(str, k, --i - k + 1);
	if (!substring || add_node_to_list(lst, substring, VAR) == -1)
		return (-1);
	return (i);
}

int	parse_variable(char *str, int i, t_list **lst, t_environ *env)
{
	int	k;

	k = i++;
	if (!str[i] || is_special_char(str[i]))
		return (handle_special_char(str, k, lst));
	if (str[i] == '?')
		return (handle_exit_status(str, i, lst, env));
	if (str[i] == '_' || ft_isalpha(str[i]))
		return (handle_variable(str, k, i, lst));
	return (k);
}
