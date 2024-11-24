/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:44:18 by yosabir           #+#    #+#             */
/*   Updated: 2024/11/02 13:10:41 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (len == 0 || (size_t)start >= (size_t)ft_strlen(s))
		return (ft_strdup(""));
	if (len < ft_strlen(s) - start)
		ptr = malloc(len + 1);
	else
		ptr = malloc(ft_strlen(s) - start + 1);
	if (!ptr)
		return (NULL);
	while ((size_t)i < len && s[start + i] != '\0')
	{
		ptr[i] = s[i + start];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
