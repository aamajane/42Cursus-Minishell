/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:28:48 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/14 18:49:31 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_global_variable(char **env)
{
	g_data.env = duplicate_env(env);
	g_data.exp = duplicate_exp(env);
	g_data.exit_code = 0;
	g_data.child_pro = 0;
	g_data.open_pipe = 0;
	g_data.open_hdoc = 0;
}

int	main(int ac, char **av, char **env)
{
	t_cmd	*cmds;
	char	*line;

	(void)ac;
	(void)av;
	init_global_variable(env);
	signal(SIGQUIT, ctrl_backslash_handler);
	signal(SIGINT, ctrl_c_handler);
	while (1337)
	{
		g_data.ctrl_c = 0;
		line = readline("╭─minishell\n╰─$ ");
		if (!line)
			ctrl_d_handler();
		else if (line && *line)
		{
			cmds = parsing(&line);
			if (cmds)
				execution(cmds);
		}
		free(line);
	}
	return (0);
}
