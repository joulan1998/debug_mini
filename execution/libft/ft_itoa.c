/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:47:37 by yosabir           #+#    #+#             */
/*   Updated: 2024/11/02 13:04:49 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	lenint(int number)
{
	long int	temp;
	int			count;

	temp = number;
	count = 0;
	if (temp == 0)
		return (1);
	while (temp != 0)
	{
		temp = temp / 10;
		count++;
	}
	if (number < 0)
		return (count + 1);
	else
		return (count);
}

char	*ft_itoa(int n)
{
	char		*ptr;
	int			index;
	long int	tmp;

	tmp = n;
	if (tmp < 0)
		tmp *= -1;
	index = lenint(n);
	ptr = (char *)malloc(lenint(n) + 1);
	if (!ptr)
		return (NULL);
	ptr[index] = '\0';
	index--;
	while (index >= 0)
	{
		ptr[index] = (tmp % 10) + 48;
		index--;
		tmp = tmp / 10;
	}
	if (n < 0)
		ptr[0] = '-';
	return (ptr);
}
