/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 20:38:19 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/14 18:23:31 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_command_path(char	*cmd)
{
	char	*cmd_path;
	char	**env_path;

	cmd_path = NULL;
	env_path = get_environment_path(cmd);
	if (command_is_builtin(cmd) != NOT_BLT || \
		(!env_path && access(cmd, F_OK) == -1))
		cmd_path = NULL;
	else if ((*cmd && ft_strchr(cmd, '/')) || (!env_path && !access(cmd, F_OK)))
		cmd_path = ft_strdup(cmd);
	else if (*cmd)
		cmd_path = check_command_path(cmd, env_path);
	free_double_pointer(env_path);
	return (cmd_path);
}

char	**get_environment_path(char *cmd)
{
	char	**env_path;
	char	*path;

	(void)cmd;
	path = get_variable_value(g_data.env, "PATH=");
	if (!path)
		return (NULL);
	env_path = ft_split(path, ':');
	if (!env_path)
		exit(puterror("Split Error"));
	return (env_path);
}

char	*check_command_path(char *cmd, char **paths)
{
	char	*path;
	char	*tmp;
	int		ret;

	ret = -1;
	while (*paths && ret == -1)
	{
		path = ft_strjoin(*paths, "/");
		tmp = path;
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		ret = access(path, X_OK);
		if (ret == -1)
			free(path);
		paths++;
	}
	if (ret == -1)
		path = NULL;
	return (path);
}
