/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:47:21 by ael-garr          #+#    #+#             */
/*   Updated: 2024/10/29 20:35:08 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_free_table(char	***table)
{
	char	**local;
	int		i;

	i = 0;
	local = *table;
	if (!local)
		return (-1);
	else
	{
		while (i < (count_table_entries(local)))
		{
			free (local[i]);
			i++;
		}
		free (local);
		return (0);
	}
	return (-1);
}
