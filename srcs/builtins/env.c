/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:12:10 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/14 15:19:12 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_env(char **args, int outfd)
{
	int	i;

	(void)args;
	g_data.exit_code = 0;
	i = 0;
	while (g_data.env[i])
	{
		ft_putstr_fd(g_data.env[i++], outfd);
		ft_putstr_fd("\n", outfd);
	}
}

char	**duplicate_env(char **str)
{
	char	**env;
	int		len;
	int		i;

	len = double_pointer_length(str);
	env = (char **)malloc(sizeof(char *) * (len + 2));
	if (!env)
		exit(puterror("Malloc Error"));
	i = -1;
	while (++i < len)
		env[i] = ft_strdup(str[i]);
	env[i] = NULL;
	return (env);
}

char	**duplicate_exp(char **env)
{
	char	**exp;
	int		len;

	exp = duplicate_env(env);
	len = double_pointer_length(env);
	free(exp[len - 1]);
	exp[len - 1] = NULL;
	return (exp);
}

char	*get_variable_value(char **env, char *var_name)
{
	int	i;
	int	j;

	if (!env)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(var_name, env[i], ft_strlen(var_name)))
		{
			j = 0;
			while (env[i][j] && env[i][j] != '=')
				j++;
			if (env[i][j] == '=')
				return (env[i] + ++j);
		}
	}
	return (NULL);
}

int	get_variable_index(char **env, char *var_name)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(var_name, env[i], ft_strlen(var_name)))
			return (i);
	return (-1);
}
