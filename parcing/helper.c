/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:42:22 by yosabir           #+#    #+#             */
/*   Updated: 2024/11/21 15:41:36 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	s = src;
	d = dst;
	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst == src)
		return (dst);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

void	error_message(t_list *lst, t_environ *env)
{
	(void)lst;
	env->exit_status = 258;
	write(1, "syntax error \n", 15);
}

int	is_special_char(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '>'
		|| c == '<' || c == '"' || c == '\'' || c == ';' || c == '$');
}

int	get_special_char(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '>' && str[i + 1] == '>')
		return (2);
	if (str[i] == '<' && str[i + 1] == '<')
		return (2);
	while (str[i] && !is_special_char(str[i]))
		i++;
	return (i);
}

int	find(char *s, char sp)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != sp)
		i++;
	return (i);
}
