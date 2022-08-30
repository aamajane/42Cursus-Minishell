/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:39:09 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/13 14:07:13 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*parsing(char **line)
{
	t_cmd	*cmds;
	char	***cmds_array;
	char	**full_cmds;

	cmds = NULL;
	add_history(*line);
	if (check_quotes_syntax(*line) && check_pipes_syntax(*line) && \
		check_redirections_syntax(*line) && join_command_line(line))
	{
		full_cmds = split_command_line(*line);
		add_spaces(&full_cmds);
		if (full_cmds)
		{
			g_data.cmds_count = double_pointer_length(full_cmds);
			cmds_array = split_commands(full_cmds);
			free_double_pointer(full_cmds);
			if (cmds_array)
			{
				expanding(&cmds_array);
				cmds = get_commands_infos(cmds_array);
				free_triple_pointer(cmds_array);
			}
		}
	}
	return (cmds);
}

int	double_pointer_length(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}
