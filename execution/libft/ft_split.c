/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:10:42 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/01 16:06:59 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_words_to_split(char *s, char c)
{
	int	i;
	int	words_count;

	words_count = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] != c) && ((s[i + 1] == c) || (s[i + 1] == '\0')))
			words_count++;
		i++;
	}
	return (words_count);
}

static char	*getword(int *i, const char *s, char c)
{
	int		currwordsize;
	int		tpos;
	int		j;
	char	*res;

	j = 0;
	while (s[*i] && s[*i] == c)
		(*i)++;
	tpos = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	currwordsize = *i - tpos;
	res = malloc(currwordsize + 1);
	if (!res)
		return (NULL);
	while (tpos + j < *i)
	{
		res[j] = s[tpos + j];
		j++;
	}
	res[j] = '\0';
	return (res);
}

static void	*full_free(char **array2D)
{
	int	i;

	i = 0;
	while (array2D[i])
	{
		if (array2D[i])
			free(array2D[i]);
		i++;
	}
	free(array2D);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		words_count;
	int		j;
	int		i;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	words_count = count_words_to_split((char *)s, c);
	result = malloc((words_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (words_count)
	{
		result[j] = getword(&i, s, c);
		if (!result[j])
			return (full_free(result));
		j++;
		words_count--;
	}
	result[j] = NULL;
	return (result);
}
