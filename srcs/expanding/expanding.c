/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 20:44:08 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/13 16:39:43 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expanding(char ****cmds_array)
{
	char	*exp_arg;
	int		i;
	int		j;

	i = -1;
	while (++i < g_data.cmds_count)
	{
		j = -1;
		while ((*cmds_array)[i][++j])
		{
			if (!ft_strncmp((*cmds_array)[i][j], "<<", \
							ft_strlen((*cmds_array)[i][j]) + 1))
				j++;
			else if (ft_strchr((*cmds_array)[i][j], '$') || \
					ft_strchr((*cmds_array)[i][j], 34) || \
					ft_strchr((*cmds_array)[i][j], 39))
			{
				exp_arg = expand_and_remove_quotes((*cmds_array)[i][j]);
				if (exp_arg)
					copy_expanded_argument(&(*cmds_array)[i][j], &exp_arg);
				else
					rearrange_array(cmds_array[i], (*cmds_array)[i][j], &j);
			}
		}
	}
}

void	copy_expanded_argument(char **cmd_array, char **exp_arg)
{
	free(*cmd_array);
	(*cmd_array) = *exp_arg;
}

void	rearrange_array(char ***cmd_array, char *str, int *j)
{
	int	k;
	int	i;

	k = 0;
	i = -1;
	while ((*cmd_array)[++i])
	{
		if (ft_strncmp((*cmd_array)[i], str, ft_strlen(str) + 1))
			(*cmd_array)[k++] = (*cmd_array)[i];
		else
			free((*cmd_array)[i]);
	}
	(*cmd_array)[k] = NULL;
	(*j)--;
}
