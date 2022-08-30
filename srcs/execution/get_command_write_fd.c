/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_write_fd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:00:36 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/13 15:19:53 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_command_write_fd(char **full_cmd, int index)
{
	int	outfd;
	int	i;

	outfd = STDOUT;
	i = -1;
	while (full_cmd[++i] && outfd != -1)
	{
		if (!ft_strncmp(full_cmd[i], ">", ft_strlen(full_cmd[i]) + 1))
			open_file_in_trunc_mode(&outfd, full_cmd[i + 1]);
		else if (!ft_strncmp(full_cmd[i], ">>", ft_strlen(full_cmd[i]) + 1))
			open_file_in_append_mode(&outfd, full_cmd[i + 1]);
	}
	if (outfd == STDOUT && index != g_data.cmds_count - 1)
		outfd = PIPE_END;
	return (outfd);
}

void	open_file_in_trunc_mode(int *outfd, char *outfile)
{
	if (outfile)
	{
		if (*outfd != STDOUT)
			close(*outfd);
		*outfd = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (*outfd == -1)
			puterror(outfile);
	}
}

void	open_file_in_append_mode(int *outfd, char *outfile)
{
	if (outfile)
	{
		if (*outfd != STDOUT)
			close(*outfd);
		*outfd = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (*outfd == -1)
			puterror(outfile);
	}
}
