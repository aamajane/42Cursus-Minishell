/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:11:50 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/13 17:19:25 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_cd(char **args, int outfd)
{
	(void)outfd;
	g_data.exit_code = 0;
	if (args[0] && !*args[0])
		return ;
	if (!args[0] || args[0][0] == '~')
		cd_home(args[0]);
	else if (!ft_strncmp(args[0], "-", ft_strlen(args[0]) + 1))
		cd_oldpwd();
	else
	{
		set_oldpwd();
		if (chdir(args[0]) == -1)
		{
			g_data.exit_code = 1;
			puterror(args[0]);
		}
		else
			set_pwd();
	}
}

void	cd_home(char *arg)
{
	char	*home;
	char	*str;

	home = get_variable_value(g_data.env, "HOME=");
	if (!home)
		return (print_cd_error("HOME"));
	if (arg && arg[1])
		str = ft_strjoin(home, arg + 1);
	else
		str = ft_strdup(home);
	set_oldpwd();
	if (chdir(str) == -1)
	{
		g_data.exit_code = 1;
		puterror(str);
	}
	else
		set_pwd();
	free(str);
}

void	cd_oldpwd(void)
{
	char	*str;

	str = get_variable_value(g_data.env, "OLDPWD=");
	if (!str)
		return (print_cd_error("OLDPWD"));
	set_oldpwd();
	if (chdir(str) == -1)
	{
		g_data.exit_code = 1;
		puterror(str);
	}
	else
		set_pwd();
}

void	set_oldpwd(void)
{
	char	*oldpwd;
	char	*cwd;
	int		len;
	int		i;

	cwd = getcwd(NULL, 0);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	free(cwd);
	i = 0;
	while (g_data.env[i] && ft_strncmp(g_data.env[i], "OLDPWD=", 7))
		i++;
	if (!g_data.env[i])
	{
		len = double_pointer_length(g_data.env);
		g_data.env[len] = oldpwd;
		g_data.env[len + 1] = NULL;
	}
	else
	{
		free(g_data.env[i]);
		g_data.env[i] = oldpwd;
	}
}

void	set_pwd(void)
{
	char	*cwd;
	int		i;

	i = 0;
	while (g_data.env[i] && ft_strncmp(g_data.env[i], "PWD=", 4))
		i++;
	if (g_data.env[i] && !ft_strncmp(g_data.env[i], "PWD=", 4))
	{
		free(g_data.env[i]);
		cwd = getcwd(NULL, 0);
		g_data.env[i] = ft_strjoin("PWD=", cwd);
		free(cwd);
	}
}
