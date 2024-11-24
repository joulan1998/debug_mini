/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_export_2_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:07:15 by ael-garr          #+#    #+#             */
/*   Updated: 2024/10/26 14:58:26 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_error_export_2_args(char *fctn_name, char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(fctn_name, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("': not a valid indetifier\n", 2);
	return (0);
}

int	ft_err_msg(t_error error)
{
	if (error.tag == TOO_MANY_ARGS)
		return (ft_putstr_fd("minishell: ", 2),
			ft_putstr_fd(error.cause, 2),
			ft_putstr_fd(": too many arguments\n", 2), error.error_no);
	if (error.tag == COMMAND_NOT_FOUND)
		return (ft_putstr_fd("minishell: ", 2),
			ft_putstr_fd(error.cause, 2),
			ft_putstr_fd(": command not found\n", 2), error.error_no);
	if (error.tag == NUMRC_ARG_REQUIRED)
		return (ft_putstr_fd("minishell: ", 2),
			ft_putstr_fd(error.cause, 2),
			ft_putstr_fd(": numeric argument required\n", 2), error.error_no);
	return (99);
}
