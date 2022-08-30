/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:12:13 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/13 23:58:44 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_exit(char **args, int outfd)
{
	int	args_count;
	int	nb;

	if (g_data.cmds_count == 1)
		ft_putstr_fd("exit\n", outfd);
	args_count = double_pointer_length(args);
	if (!args_count && g_data.cmds_count > 1)
		exit(0);
	if (!args_count)
		exit(g_data.exit_code);
	nb = ft_atoi(args[0]);
	if ((nb == 0 && ft_strncmp(args[0], "0", ft_strlen(args[0]) + 1) && \
		ft_strncmp(args[0], "-9223372036854775808", ft_strlen(args[0]) + 1)) || \
		(nb == -1 && ft_strncmp(args[0], "-1", ft_strlen(args[0]) + 1) && \
		ft_strncmp(args[0], "9223372036854775807", ft_strlen(args[0]) + 1)))
		exit(print_exit_numeric_error(args[0]));
	if (args_count > 1)
		return (print_exit_argument_error());
	g_data.exit_code = nb;
	exit(g_data.exit_code);
}
