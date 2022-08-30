/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:12:03 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/14 14:06:12 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_echo(char **args, int outfd)
{
	int	new_line;
	int	i;

	g_data.exit_code = 0;
	new_line = 1;
	i = 0;
	if (args[i] && is_n_option(args[i]))
	{
		new_line = 0;
		while (args[i] && is_n_option(args[i]))
			i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i++], outfd);
		if (args[i])
			ft_putstr_fd(" ", outfd);
	}
	if (new_line)
		ft_putstr_fd("\n", outfd);
}

int	is_n_option(char *arg)
{
	int	i;

	if (arg[0] != '-' || (arg[0] == '-' && arg[1] != 'n'))
		return (0);
	i = 1;
	while (arg[i] == 'n')
		i++;
	if (arg[i] && arg[i] != 'n')
		return (0);
	return (1);
}
