/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_read_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:56:19 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/14 18:49:59 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_command_read_fd(char **full_cmd, int index)
{
	char	*infile;
	int		infd;
	int		i;

	infd = STDIN;
	i = -1;
	while (full_cmd[++i])
	{
		if (!ft_strncmp(full_cmd[i], "<", ft_strlen(full_cmd[i]) + 1) && \
			infd != -1)
			infile = open_file_in_read_mode(&infd, full_cmd[i + 1]);
		else if (!ft_strncmp(full_cmd[i], "<<", ft_strlen(full_cmd[i]) + 1) && \
				!g_data.ctrl_c)
			open_heredoc(&infd, full_cmd[i + 1]);
	}
	if (infd == STDIN && index != 0)
		infd = PIPE_END;
	if (infd == -1)
		puterror(infile);
	return (infd);
}

char	*open_file_in_read_mode(int *infd, char *infile)
{
	if (infile)
	{
		if (*infd != STDIN)
			close(*infd);
		*infd = open(infile, O_RDONLY);
	}
	return (infile);
}

void	open_heredoc(int *infd, char *infile)
{
	int	fd;

	if (infile)
	{
		if (*infd == -1)
		{
			fd = heredoc(infile);
			close(fd);
		}
		else
		{
			if (*infd != STDIN)
				close(*infd);
			*infd = heredoc(infile);
			if (*infd == -1)
				puterror(infile);
		}
	}
}

int	heredoc(char *delimiter)
{
	t_hdoc	hdoc;

	hdoc.quote = 0;
	if (ft_strchr(delimiter, 34) || ft_strchr(delimiter, 39))
	{
		hdoc.quote = 1;
		remove_delimiter_qoute(&delimiter);
	}
	hdoc.dupfd = dup(STDIN);
	if (pipe(hdoc.end) == -1)
		exit(puterror("Pipe Error"));
	read_heredoc_lines(&hdoc, delimiter);
	dup(hdoc.dupfd);
	close(hdoc.dupfd);
	close(hdoc.end[1]);
	return (hdoc.end[0]);
}

void	read_heredoc_lines(t_hdoc *hdoc, char *delimiter)
{
	g_data.open_hdoc = 1;
	while (1337)
	{
		hdoc->line = readline("heredoc> ");
		if (!hdoc->line)
			break ;
		if (!ft_strncmp(hdoc->line, delimiter, ft_strlen(hdoc->line) + 1))
		{
			free(hdoc->line);
			break ;
		}
		if (hdoc->quote == 0 && ft_strchr(hdoc->line, '$'))
			expand_heredoc_variable(&hdoc->line);
		ft_putendl_fd(hdoc->line, hdoc->end[1]);
		free(hdoc->line);
	}
	g_data.open_hdoc = 0;
}
