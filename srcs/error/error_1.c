/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:47:42 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/14 16:15:10 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	puterror(char *str)
{
	ft_putstr_fd("minishell: ", STDERR);
	perror(str);
	return (EXIT_FAILURE);
}

int	print_syntax_error(char *str)
{
	g_data.exit_code = 258;
	ft_putstr_fd("minishell: syntax error near ", STDERR);
	ft_putendl_fd(str, STDERR);
	return (0);
}

void	print_command_error(char *str)
{
	g_data.exit_code = 127;
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putstr_fd(": command not found\n", STDERR);
}

void	print_path_error(char *str)
{
	g_data.exit_code = 127;
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putstr_fd(": No such file or directory\n", STDERR);
}
