/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:26:53 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/13 14:14:10 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_commands_data(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = -1;
	while (++i < g_data.cmds_count)
	{
		free_double_pointer((cmd + i)->args);
		if ((cmd + i)->path)
			free((cmd + i)->path);
	}
	free(cmd);
}

void	free_double_pointer(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	free_triple_pointer(char ***str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (i < g_data.cmds_count)
		free_double_pointer(str[i++]);
	free(str);
}
