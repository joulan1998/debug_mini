/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:40:58 by yosabir           #+#    #+#             */
/*   Updated: 2024/11/26 22:35:13 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_variable(t_list *token, t_environ *env)
{
	t_list	*current;
	char	*string;

	current = token;
	string = ft_strtrim(token->content, "$");
	free(token->content);
	while (env)
	{
		if (ft_strcmp(string, env->var) == 0)
			return (free(string), ft_strdup(env->value));
		else if (ft_strcmp(string, "?") == 0)
			return (free(string), ft_itoa(env->exit_status));
		env = env->next;
	}
	free(string);
	return (NULL);
}

char	*extract_variable(char *s)
{
	int		i;
	int		x;
	char	*result;
	char	*ptr;

	result = NULL;
	ptr = NULL;
	i = 0;
	x = 0;
	i = find(s, '$') + 1;
	if ((size_t)i >= ft_strlen(s))
		return (NULL);
	result = ft_substr(s, i, ft_strlen(s));
	x = get_variable_index(result);
	free(result);
	ptr = ft_substr(s, i, x);
	return (ptr);
}

char	*contact_varstr(char *string, char *variable)
{
	int		start;
	int		end;
	char	*s1;
	char	*s2;
	char	*concat_s1_var;

	start = find(string, '$');
	end = get_special_char(string + start + 1);
	if (start == 0)
		s1 = ft_strdup("");
	else
		s1 = ft_substr(string, 0, start);
	concat_s1_var = ft_strjoin(s1, variable);
	s2 = ft_substr(string, start + 1 + end, ft_strlen(string));
	free(s1);
	s1 = ft_strjoin(concat_s1_var, s2);
	return (free(s2), free(string), free(concat_s1_var), s1);
}
