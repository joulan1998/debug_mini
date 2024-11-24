/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 10:33:50 by ael-garr          #+#    #+#             */
/*   Updated: 2024/10/30 14:01:48 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		ft_putchar(str[i++]);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	sort_and_print(char	**table)
{
	int	j;
	int	x;
	int	n;

	n = count_table_entries (table);
	if (table == NULL || n == 0)
		return (0);
	x = 0;
	while (x < n - 1)
	{
		j = 0;
		while (j < n - 1 - x)
		{
			if (ft_strncmp (table[j], table[j + 1], 1) > 0)
				ft_swap (&table[j], &table[j + 1]);
			j++;
		}
		x++;
	}
	j = 0;
	while (j < n)
		printf("declare -x %s\n", table[j++]);
	return (0);
}
