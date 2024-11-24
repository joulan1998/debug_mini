/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:21:55 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/17 10:07:16 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_value(char *line)
{
	char	*local;
	char	*result;
	int		i;

	local = line;
	i = 0;
	if (!ft_strchr(line, '='))
		return (NULL);
	result = malloc(ft_strlen(ft_strchr(line, '=')));
	while (*local != '=')
		local++;
	if (*local == '=')
		local++;
	while (*local)
	{
		result[i] = *local;
		i++;
		local++;
	}
	result[i] = '\0';
	return (result);
}

int	to_alloc(char *s, char c)
{
	char	*res;
	int		result;

	res = s;
	result = 0;
	while (res[result] && res[result] != c)
		result++;
	return (result);
}

char	*extract_key(char *string)
{
	char	*result;
	int		i;

	i = 0;
	if (!*string)
		return (NULL);
	result = malloc(to_alloc(string, '=') + 1);
	if (!result)
		return (NULL);
	while (string[i] && string[i] != '=')
	{
		result[i] = string[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

int	check_syntax_for_export(char *string)
{
	char	*local;
	int		i;

	i = -1;
	local = extract_key(string);
	if (ft_strlen(local) == 1)
	{
		if ((ft_isalpha(local[0])) || local[0] == '_')
			return (free(local), 1);
		else
			return (free(local), 0);
	}
	else
	{
		while (++i < ((int)ft_strlen(local) - 1))
		{
			if (!ft_isalpha(local[i])
				&& !ft_isdigit(local[i]) && local[i] != '_')
				return (free(local), 0);
		}
		if (ft_isalpha(local[i]) || ft_isdigit(local[i])
			|| local[i] == '+' || local[i] == '_')
			return (free(local), 1);
	}
	return (free(local), 0);
}

int	count_table_entries(char **table)
{
	int	i;

	i = 0;
	if (!table || !*table)
		return (0);
	while (table[i])
		i++;
	return (i);
}
