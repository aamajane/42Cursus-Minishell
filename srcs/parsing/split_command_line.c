/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:19:43 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/13 15:48:28 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**split_command_line(char *line)
{
	char	**full_cmds;
	int		i;

	replace_quote_character(line, '|', 127);
	full_cmds = ft_split(line, '|');
	if (!full_cmds)
		exit(puterror("Split Error"));
	i = -1;
	while (full_cmds[++i])
		replace_quote_character(full_cmds[i], 127, '|');
	return (full_cmds);
}

void	replace_quote_character(char *line, char target, char replacement)
{
	char	quote;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
			{
				if (line[i] == target)
					line[i] = replacement;
				i++;
			}
		}
		if (line[i])
			i++;
	}
}
