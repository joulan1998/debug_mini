/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinning_and_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:55:09 by ael-garr          #+#    #+#             */
/*   Updated: 2024/10/29 20:34:06 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*joinning_and_free(char *s1, char	*s2)
{
	char	*tmp;

	if (!s1 && s2)
		return (ft_strdup (s2));
	else if (s1 && !s2)
		return (ft_strdup (s1));
	else if (!s1 && !s2)
		return (NULL);
	else
	{
		tmp = ft_strjoin(s1, s2);
		free (s1);
		s1 = tmp;
	}
	return (s1);
}
