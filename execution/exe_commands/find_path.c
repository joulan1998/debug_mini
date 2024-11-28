/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:17:20 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/27 17:18:20 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_path(char	*path, char *ftn)
{
	char	**table;
	char	*res;
	int		i;

	i = 0;
	table = ft_split(path, ':');
	free(path);
	while (i < count_table_entries(table))
	{
		res = ft_strjoin(table[i], "/");
		res = joinning_and_free(res, ftn);
		if (access (res, X_OK) == 0)
		{
			ft_free_table (&table);
			return (res);
		}
		free(res);
		i++;
	}
	ft_free_table(&table);
	return (ft_strdup(ftn));
}
