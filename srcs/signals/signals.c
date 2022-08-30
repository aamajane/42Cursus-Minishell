/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:42:45 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/14 18:51:17 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ctrl_backslash_handler(int sig)
{
	(void)sig;
	if (g_data.child_pro)
		ft_putstr_fd("Quit: 3\n", STDOUT);
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ctrl_c_handler(int sig)
{
	(void)sig;
	if (!g_data.child_pro && !g_data.open_pipe && !g_data.open_hdoc)
	{
		g_data.exit_code = 1;
		rl_replace_line("", 0);
		ft_putstr_fd("\n╭─minishell\n", STDOUT);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_data.child_pro || g_data.open_pipe || g_data.open_hdoc)
	{
		ft_putstr_fd("\n", STDOUT);
		if (g_data.open_pipe || g_data.open_hdoc)
		{
			g_data.ctrl_c = 1;
			close(STDIN);
		}
	}
}

void	ctrl_d_handler(void)
{
	ft_putstr_fd("exit\n", STDOUT);
	exit(0);
}
