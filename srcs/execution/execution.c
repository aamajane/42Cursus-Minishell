/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 20:23:09 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/14 18:08:42 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execution(t_cmd *cmds)
{
	t_exec	exec;

	creat_pipes(&exec.pipex);
	exec.i = -1;
	while (++exec.i < g_data.cmds_count)
	{
		get_command_pipe_fd(&exec.pipex, cmds + exec.i);
		exec.builtin = get_builtin_value((cmds + exec.i)->args);
		if (exec.builtin != NOT_BLT && g_data.cmds_count == 1)
			execute_builtin(cmds + exec.i, exec.builtin);
		else
		{
			g_data.child_pro = 1;
			(cmds + exec.i)->pid = fork();
			if ((cmds + exec.i)->pid == -1)
				exit(puterror("Fork Error"));
			if ((cmds + exec.i)->pid == 0)
				execute_command(cmds + exec.i, &exec.pipex, exec.builtin);
		}
	}
	close_all_fd(cmds, &exec.pipex);
	if (g_data.child_pro)
		wait_child_processes(cmds);
	free_commands_data(cmds);
}

void	close_all_fd(t_cmd *cmds, t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < g_data.cmds_count)
	{
		if ((cmds + i)->infd != STDIN)
			close((cmds + i)->infd);
		if ((cmds + i)->outfd != STDOUT)
			close((cmds + i)->outfd);
	}
	close(pipex->p1_end[0]);
	close(pipex->p1_end[1]);
	close(pipex->p2_end[0]);
	close(pipex->p2_end[1]);
}
