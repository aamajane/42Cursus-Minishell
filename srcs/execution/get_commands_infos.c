/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands_infos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:49:20 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/14 17:02:16 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*get_commands_infos(char ***cmds_array)
{
	t_cmd	*cmds;
	int		i;

	cmds = (t_cmd *)malloc(sizeof(t_cmd) * g_data.cmds_count);
	if (!cmds)
		exit(puterror("Malloc Error"));
	i = -1;
	while (++i < g_data.cmds_count)
	{
		(cmds + i)->outfd = -1;
		(cmds + i)->args = NULL;
		(cmds + i)->path = NULL;
		(cmds + i)->index = i;
		(cmds + i)->infd = get_command_read_fd(cmds_array[i], i);
		if ((cmds + i)->infd != -1 && !g_data.ctrl_c)
		{
			(cmds + i)->outfd = get_command_write_fd(cmds_array[i], i);
			(cmds + i)->args = get_command_arguments(cmds_array[i]);
			if ((cmds + i)->args)
				(cmds + i)->path = get_command_path((cmds + i)->args[0]);
		}
	}
	check_commands_errors(cmds);
	return (cmds);
}

void	check_commands_errors(t_cmd *cmds)
{
	char	*env_path;
	int		i;

	env_path = get_variable_value(g_data.env, "PATH=");
	i = -1;
	while (++i < g_data.cmds_count)
	{
		if ((cmds + i)->args && !(cmds + i)->path && \
			command_is_builtin((cmds + i)->args[0]) == NOT_BLT)
		{
			if (env_path)
				print_command_error((cmds + i)->args[0]);
			else if (access((cmds + i)->args[0], F_OK) == -1)
				print_path_error((cmds + i)->args[0]);
		}
	}
}
