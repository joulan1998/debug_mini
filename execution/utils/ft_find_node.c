/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:32:21 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/28 12:30:32 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_find_node(t_minishell *data, char	*str)
{
	char		*local;
	t_environ	*lst;

	local = NULL;
	lst = data->env_lst;
	while (lst->next && lst->var && lst->value)
	{
		if (lst->var && lst->value)
		{
			if (ft_strncmp(lst->var, str, (ft_strlen(lst->var))) == 0)
			{
				local = ft_strdup(lst->value);
				if (!local)
					return (NULL);
				return (local);
			}
		}
		lst = lst->next;
	}
	// if (!local)
	// 	return (ft_strdup(OWN_PATH));
	return (NULL);
}
