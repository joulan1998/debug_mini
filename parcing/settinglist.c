/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settinglist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:44:50 by yosabir           #+#    #+#             */
/*   Updated: 2024/11/23 22:59:01 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_arg_to_set_args(set_args *cmd_args, char *new_arg)
{
	char	**new_args;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (cmd_args->args && cmd_args->args[count])
		count++;
	new_args = (char **)malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return ;
	while (i < count)
	{
		new_args[i] = cmd_args->args[i];
		i++;
	}
	new_args[count] = ft_strdup(new_arg);
	if (!new_args[count])
		return ;
	new_args[count + 1] = NULL;
	free(cmd_args->args);
	cmd_args->args = new_args;
}

void	storing_args(t_list **current, set_args *cmd_args, t_environ *env)
{
	int	add;

	add = 1;
	cmd_args->input = 0;
	cmd_args->output = 1;
	if((*current)->command ==  PIPE)
			*current = (*current)->next;
	while (*current &&  (*current)->command !=  PIPE)
	{
		if ((*current)->command == WORD || (*current)->command == S_QUOTE
			|| (*current)->command == D_QUOTE || (*current)->command == VAR)
		{
			if (add)
				process_argument(current, cmd_args);
			add = 1;
		}
		else if ((*current)->command == RD_IN || (*current)->command == RD_OUT
			|| (*current)->command == APPEND || (*current)->command == HEREDOC)
		{
			add = 0;
			handle_red(*current, cmd_args, env);
		}
		*current = (*current)->next;
	}
}

set_args	*init_set_args(void)
{
	set_args	*cmd_args;

	cmd_args = (set_args *)malloc(sizeof(set_args));
	if (!cmd_args)
		return (NULL);
	cmd_args->args = NULL;
	cmd_args->input = 0;
	cmd_args->output = 1;
	cmd_args->next = NULL;
	return (cmd_args);
}

static void	linkargs(set_args **lastargs, set_args **arglist, set_args *newargs)
{
	if (*lastargs)
		(*lastargs)->next = newargs;
	else
		*arglist = newargs;
	*lastargs = newargs;
}

set_args	*args(t_list **lst, t_environ *env, int num)
{
	t_list		*current;
	set_args	*args_list;
	set_args	*last_args;
	set_args	*arg;
	int			i;

	current = *lst;
	args_list = NULL;
	last_args = NULL;
	num = pipen(lst);
	i = 0;
	while (i < num)
	{
		arg = init_set_args();
		if (!arg)
			return (NULL);
		linkargs(&last_args, &args_list, arg);
		storing_args(&current, arg, env);
		i++;
	}
	return (args_list);
}
