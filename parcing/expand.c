/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:25:02 by yosabir           #+#    #+#             */
/*   Updated: 2024/11/23 20:30:43 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_variable_index(char *s)
{
	int	i;

	i = 1;
	if (s[i] && s[i] == '?')
		return (i + 1);
	if (s[i] && s[i] != '_' && !ft_isalpha(s[i]))
		return (get_special_char(&s[i]) + 1);
	while (s[i])
	{
		if (s[i] && s[i] != '_' && !ft_isalpha(s[i]) && !ft_isdigit(s[i]))
			return (i);
		i++;
	}
	return (i);
}

char	*get_variable_value(char *variable, t_environ *env)
{
	t_environ	*ev;
	char		*status;

	ev = env;
	if (*variable == '?')
	{
		variable += 1;
		status = ft_itoa(env->exit_status);
		free(status);
		return (ft_strjoin(status, variable));
	}
	while (ev)
	{
		if (ft_strcmp(variable, ev->var) == 0)
			return (ft_strdup(ev->value));
		ev = ev->next;
	}
	return (env->exit_status = 0, NULL);
}

char	*expand_here_doc(char *string, int dont_expand, t_environ *env)
{
	char	*variable;
	char	*value;

	variable = NULL;
	value = NULL;
	if (!dont_expand)
		return (ft_strdup(string));
	variable = extract_variable(string);
	while (variable && *variable)
	{
		value = get_variable_value(variable, env);
		string = contact_varstr(string, value);
		free(value);
		free(variable);
		variable = extract_variable(string);
	}
	return (free(variable), string);
}

char	*expand_double_q_variable(t_list *token, t_environ *env)
{
	char	*variable;
	char	*value;
	char	*string;
	char	*s;

	variable = NULL;
	value = NULL;
	string = NULL;
	s = NULL;
	s = token->content;
	string = ft_strtrim(s, "\"");
	free(s);
	variable = extract_variable(string);
	while (variable && *variable)
	{
		value = get_variable_value(variable, env);
		string = contact_varstr(string, value);
		free(variable);
		variable = extract_variable(string);
	}
	return (free(variable), free(value), string);
}

t_list	*expanding(t_list *list, t_environ *env)
{
	t_list	*current;
	char	*new_content;

	current = list;
	while (current)
	{
		current = skip_spaces(current);
		if (!current)
			return (NULL);
		if (current && current->command == VAR)
			current->content = expand_variable(current, env);
		else if (current && current->command == D_QUOTE)
			current->content = expand_double_q_variable(current, env);
		else if (current->command == S_QUOTE)
		{
			new_content = ft_strtrim(current->content, "'");
			free(current->content);
			current->content = new_content;
		}
		current = current->next;
	}
	return (list);
}
