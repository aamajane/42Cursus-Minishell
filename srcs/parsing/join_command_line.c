/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_command_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:30:38 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/14 18:50:08 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	join_command_line(char **line)
{
	t_join	join;

	if (check_last_pipe(*line))
	{
		join.dupfd = dup(STDIN);
		join.pipe_line = ft_strdup("");
		if (!read_open_pipe(&join, line))
			return (0);
		add_joined_line_to_history(&join, line);
	}
	return (1);
}

int	read_open_pipe(t_join *join, char **line)
{
	g_data.open_pipe = 1;
	while (check_last_pipe(join->pipe_line) || full_spaces(join->pipe_line))
	{
		join->cmd_line = readline("pipe> ");
		if (!join->cmd_line)
		{
			if (!g_data.ctrl_c)
				print_syntax_error("EOF");
			return (add_joined_line_to_history(join, line));
		}
		join->tmp = join->pipe_line;
		join->pipe_line = ft_strjoin(join->tmp, join->cmd_line);
		free(join->cmd_line);
		free(join->tmp);
		if (!check_quotes_syntax(join->pipe_line) || \
			!check_pipes_syntax(join->pipe_line) || \
			!check_redirections_syntax(join->pipe_line))
			return (add_joined_line_to_history(join, line));
	}
	return (1);
}

int	check_last_pipe(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (line[i] == ' ')
		i--;
	if (line[i] == '|')
		return (1);
	return (0);
}

int	full_spaces(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ')
			return (0);
	return (1);
}

int	add_joined_line_to_history(t_join *join, char **line)
{
	g_data.open_pipe = 0;
	dup(join->dupfd);
	close(join->dupfd);
	if (g_data.ctrl_c)
	{
		g_data.exit_code = 1;
		free(join->pipe_line);
	}
	else
	{
		join->tmp = *line;
		*line = ft_strjoin(join->tmp, join->pipe_line);
		free(join->pipe_line);
		free(join->tmp);
		add_history(*line);
	}
	return (0);
}
