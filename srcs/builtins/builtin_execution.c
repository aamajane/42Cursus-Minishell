/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:42:49 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/13 17:46:52 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	command_is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd) + 1))
		return (BLT_ECHO);
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd) + 1))
		return (BLT_CD);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd) + 1))
		return (BLT_PWD);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd) + 1))
		return (BLT_EXPORT);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd) + 1))
		return (BLT_UNSET);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd) + 1))
		return (BLT_ENV);
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd) + 1))
		return (BLT_EXIT);
	return (NOT_BLT);
}

void	execute_builtin(t_cmd *cmd, int builtin)
{
	void	(*exec_builtin[7])(char **, int outfd);

	if (cmd->infd == -1 || cmd->outfd == -1)
	{
		g_data.exit_code = 1;
		return ;
	}
	exec_builtin[BLT_ECHO] = &builtin_echo;
	exec_builtin[BLT_CD] = &builtin_cd;
	exec_builtin[BLT_PWD] = &builtin_pwd;
	exec_builtin[BLT_EXPORT] = &builtin_export;
	exec_builtin[BLT_UNSET] = &builtin_unset;
	exec_builtin[BLT_ENV] = &builtin_env;
	exec_builtin[BLT_EXIT] = &builtin_exit;
	if (g_data.cmds_count == 1)
		exec_builtin[builtin](cmd->args + 1, cmd->outfd);
	else
		exec_builtin[builtin](cmd->args + 1, STDOUT);
}

int	get_builtin_value(char **args)
{
	int	builtin;

	if (args)
		builtin = command_is_builtin(args[0]);
	else
		builtin = NOT_BLT;
	return (builtin);
}
