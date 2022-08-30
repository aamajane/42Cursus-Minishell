/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:03:38 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/13 13:42:58 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	***split_commands(char **full_cmds)
{
	char	***cmds_array;
	int		i;

	cmds_array = (char ***)malloc(sizeof(char **) * g_data.cmds_count);
	if (!cmds_array)
		exit(puterror("Malloc Error"));
	i = -1;
	while (full_cmds[++i])
	{
		replace_quote_character(full_cmds[i], ' ', 127);
		cmds_array[i] = ft_split(full_cmds[i], ' ');
		if (!cmds_array[i])
			exit(puterror("Split Error"));
		if (!*cmds_array[i])
		{
			free_triple_pointer(cmds_array);
			return (NULL);
		}
	}
	reset_commands_quotes_spaces(cmds_array);
	return (cmds_array);
}

void	reset_commands_quotes_spaces(char ***cmds_array)
{
	int	i;
	int	j;

	i = -1;
	while (++i < g_data.cmds_count)
	{
		j = 0;
		while (cmds_array[i][j])
			replace_quote_character(cmds_array[i][j++], 127, ' ');
	}
}
