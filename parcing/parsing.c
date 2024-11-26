/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 11:07:04 by yosabir           #+#    #+#             */
/*   Updated: 2024/11/25 17:12:38 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_single_char(char *str, int i, t_list **lst)
{
	t_list	*new_node;
	char	*substring;

	substring = ft_substr(str, i, 1);
	new_node = ft_lstnew(substring);
	if (!substring || !new_node)
	{
		free(substring);
		return ;
	}
	if (str[i] == '|')
		new_node->command = PIPE;
	else if (str[i] == '<')
		new_node->command = RD_IN;
	else if (str[i] == '>')
		new_node->command = RD_OUT;
	// free(substring);
	ft_lstadd_back(lst, new_node);
}

static int	parse_operator(char *str, int i, t_list **lst)
{
	t_list	*new_node;
	char	*substring;

	if ((str[i] == '<' && str[i + 1] == '<')
		|| (str[i] == '>' && str[i + 1] == '>'))
	{
		substring = ft_substr(str, i, 2);
		new_node = ft_lstnew(substring);
		if (!substring || !new_node)
		{
			free(substring);
			return (-1);
		}
		if (str[i] == '<')
			new_node->command = HEREDOC;
		else if (str[i] == '>')
			new_node->command = APPEND;
		ft_lstadd_back(lst, new_node);
		i++;
	}
	else
		handle_single_char(str, i, lst);
	return (i);
}

int	parse_quote(char *str, int i, t_list **lst)
{
	t_list	*node;
	char	*substring;
	char	quote_char;
	int		j;

	j = i;
	quote_char = str[i];
	i++;
	while (str[i] && str[i] != quote_char)
		i++;
	if (str[i] == '\0')
		return (free(str), -1);
	substring = ft_substr(str, j, (i - j) + 1);
	node = ft_lstnew(substring);
	if (!substring || !node)
		return (free(substring), -1);
	if (quote_char == '"')
		node->command = D_QUOTE;
	else if (quote_char == '\'')
		node->command = S_QUOTE;
	ft_lstadd_back(lst, node);
	return (i);
}

t_list	*parsing(char *str, t_environ *env)
{
	t_list	*lst;
	char	*s;
	int		i;

	i = 0;
	lst = NULL;
	s = ft_strtrim(str, " ");
	while (s[i])
	{
		if (s[i] == '|' || s[i] == '<' || s[i] == '>')
			i = parse_operator(s, i, &lst);
		else if (s[i] == '$')
			i = parse_variable(s, i, &lst, env);
		else if (s[i] == '\'' || s[i] == '"')
			i = parse_quote(s, i, &lst);
		else if (s[i] == ' ' || s[i] == '\t')
			i = parse_spaces(s, i, &lst);
		else
			i = parse_word(s, i, &lst);
		if (i < 0)
			return (free_t_list(lst), NULL);
		i++;
	}
	free(s);
	return (lst);
}
