/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:02:29 by ael-garr          #+#    #+#             */
/*   Updated: 2024/10/26 15:00:02 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*fill(char const	*s1, char const	*s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	ptr = malloc(((i + j) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		ptr[i++] = s1[j++];
	j = 0;
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	result = fill(s1, s2);
	return (result);
}

// static char	*fill(char const	*s1, char const	*s2)
// {
// 	char	*ptr;
// 	int		i;
// 	int		j;

// 	i = ft_strlen(s1);
// 	j = ft_strlen(s2);
// 	ptr = malloc(((i + j) + 1) * sizeof(char));
// 	if (!ptr)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (s1[i])
// 		ptr[i++] = s1[j++];
// 	j = 0;
// 	while (s2[j])
// 		ptr[i++] = s2[j++];
// 	ptr[i] = '\0';
// 	return (ptr);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*result;

// 	if (!s1 && s2)
// 		return (NULL);
// 	if (!s1)
// 		return (ft_strdup(s2));
// 	if (!s2)
// 		return (ft_strdup(s1));
// 	result = fill(s1, s2);
// 	return (result);
// }
// static size_t	ft_count_words(char const *s, char c)
// {
// 	size_t	i;
// 	size_t	word_count;
// 	size_t	s_len;

// 	i = 0;
// 	word_count = 0;
// 	if (!s)
// 		return (0);
// 	s_len = ft_strlen(s);
// 	while (s[i] != '\0')
// 	{
// 		if (i + 1 <= s_len && s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
// 			word_count++;
// 		i++;
// 	}
// 	return (word_count);
// }

// static char	**clean_memory(char **s, size_t len)
// {
// 	size_t	i;

// 	if (!s)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		free(s[i]);
// 		i++;
// 	}
// 	free(s);
// 	return (NULL);
// }

// static char	**ft_get_words(char **s_split, const char *s, char c)
// {
// 	size_t	start;
// 	size_t	end;
// 	size_t	i;
// 	size_t	j;

// 	start = 0;
// 	end = 0;
// 	i = 0;
// 	j = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (i == 0 || (s[i - 1] == c && s[i] != c))
// 			start = i;
// 		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
// 		{
// 			end = i;
// 			s_split[j] = ft_substr(s, start, end - start + 1);
// 			if (s_split[j] == NULL)
// 				return (clean_memory(s_split, j));
// 			j++;
// 		}
// 		i++;
// 	}
// 	s_split[j] = NULL;
// 	return (s_split);
// }

// char	**ft_split(char const *s, char c)
// {
// 	size_t	words_count;
// 	char	**s_split;

// 	if (!s)
// 		exit(1);
// 	words_count = ft_count_words(s, c);
// 	s_split = malloc(sizeof(char *) * (words_count + 1));
// 	if (!s_split)
// 		return (NULL);
// 	s_split = ft_get_words(s_split, s, c);
// 	return (s_split);
// }