/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:12:37 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/13 17:18:54 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_unset(char **args, int outfd)
{
	char	*var_name;
	int		i;

	(void)outfd;
	g_data.exit_code = 0;
	if (!args[0])
		return ;
	if (!args[0][0])
		return (print_variable_name_error("unset", "`'"));
	i = -1;
	while (args[++i])
	{
		if (check_variable_name(args[i]))
		{
			var_name = ft_strjoin(args[i], "=");
			g_data.env = unset_variable(g_data.env, var_name);
			g_data.exp = unset_variable(g_data.exp, var_name);
			free(var_name);
		}
		else
			print_variable_name_error("unset", args[i]);
	}
}

int	check_variable_name(char *var_name)
{
	int	i;

	if (!ft_isalpha(var_name[0]) && var_name[0] != '_')
		return (0);
	i = -1;
	while (var_name[++i])
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			return (0);
	return (1);
}

char	**unset_variable(char **env, char *var_name)
{
	char	**new_env;
	int		len;
	int		i;
	int		j;

	if (!get_variable_value(env, var_name))
		return (env);
	len = double_pointer_length(env);
	new_env = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new_env)
		exit(puterror("Malloc Error"));
	i = -1;
	j = 0;
	while (++i < len)
		if (ft_strncmp(var_name, env[i], ft_strlen(var_name)))
			new_env[j++] = ft_strdup(env[i]);
	new_env[j] = NULL;
	free_double_pointer(env);
	return (new_env);
}
