/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:48:05 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/10 16:06:41 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_cd_error(char *str)
{
	g_data.exit_code = 1;
	ft_putstr_fd("minishell: cd: ", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putstr_fd(" not set\n", STDERR);
}

void	print_pwd_error(char c)
{
	g_data.exit_code = 1;
	ft_putstr_fd("minishell: pwd: -", STDERR);
	ft_putchar_fd(c, STDERR);
	ft_putstr_fd(": invalid option\n", STDERR);
}

void	print_variable_name_error(char *cmd, char *str)
{
	g_data.exit_code = 1;
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putstr_fd(": not a valid identifier\n", STDERR);
}

void	print_exit_argument_error(void)
{
	g_data.exit_code = 1;
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
}

int	print_exit_numeric_error(char *str)
{
	g_data.exit_code = 255;
	ft_putstr_fd("minishell: exit: ", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putstr_fd(": numeric argument required\n", STDERR);
	return (255);
}
