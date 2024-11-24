/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:58:27 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/03 17:59:03 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	initialize_fds(int ***table, int n)
{
	int	i;

	i = 0;
	*table = malloc(n * sizeof(int *));
	if (!(*table))
		return (-1);
	while (i < n)
	{
		(*table)[i] = malloc(2 * sizeof(int));
		if (!(*table)[i])
			return (-1);
		i++;
	}
	return (i);
}

void	close_fd(int *n)
{
	if (!n)
		return ;
	while (*n > 0)
	{
		close(*n);
		n++;
	}
}

int	dupping(int old, int new)
{
	if (dup2(old, new) == -1)
		return (-1);
	close(old);
	return (0);
}
