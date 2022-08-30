/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_pipe_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 19:00:51 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/13 15:26:09 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	creat_pipes(t_pipex *pipex)
{
	if (pipe(pipex->p1_end) == -1)
		exit(puterror("Pipe Error"));
	if (pipe(pipex->p2_end) == -1)
		exit(puterror("Pipe Error"));
}

void	get_command_pipe_fd(t_pipex *pipex, t_cmd *cmd)
{
	if (cmd->infd == PIPE_END)
		cmd->infd = get_pipe_read_fd(pipex, cmd->index);
	if (cmd->outfd == PIPE_END)
		cmd->outfd = get_pipe_write_fd(pipex, cmd->index);
}

int	get_pipe_read_fd(t_pipex *pipex, int index)
{
	int	infd;

	if (!(index % 2))
		infd = pipex->p2_end[0];
	else
		infd = pipex->p1_end[0];
	return (infd);
}

int	get_pipe_write_fd(t_pipex *pipex, int index)
{
	int	outfd;

	if (!(index % 2))
	{
		close(pipex->p1_end[0]);
		close(pipex->p1_end[1]);
		if (pipe(pipex->p1_end) == -1)
			exit(puterror("Pipe Error"));
		outfd = pipex->p1_end[1];
	}
	else
	{
		close(pipex->p2_end[0]);
		close(pipex->p2_end[1]);
		if (pipe(pipex->p2_end) == -1)
			exit(puterror("Pipe Error"));
		outfd = pipex->p2_end[1];
	}
	return (outfd);
}
