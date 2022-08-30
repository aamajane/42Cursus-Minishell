/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 20:21:48 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/14 18:08:41 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_command(t_cmd *cmd, t_pipex *pipex, int builtin)
{
	if (cmd->infd == -1 || cmd->outfd == -1)
		exit(1);
	if (dup2(cmd->infd, STDIN) == -1)
		exit(puterror("Dup2 Error"));
	if (dup2(cmd->outfd, STDOUT) == -1)
		exit(puterror("Dup2 Error"));
	close_all_fd(cmd - cmd->index, pipex);
	if (builtin != NOT_BLT)
	{
		execute_builtin(cmd, builtin);
		exit(g_data.exit_code);
	}
	if (!cmd->args)
		exit(0);
	if (cmd->path)
		if (execve(cmd->path, cmd->args, g_data.env) == -1)
			puterror(cmd->args[0]);
	if (!access(cmd->path, F_OK))
		exit(126);
	exit(127);
}

void	wait_child_processes(t_cmd *cmds)
{
	int	i;
	int	status;

	i = -1;
	while (++i < g_data.cmds_count)
	{
		if (waitpid((cmds + i)->pid, &status, 0) == -1)
			exit(puterror("Waitpid Error"));
		if (status == 2 || status == 3)
			g_data.exit_code = 128 + status;
		else
			g_data.exit_code = WEXITSTATUS(status);
	}
	g_data.child_pro = 0;
}
