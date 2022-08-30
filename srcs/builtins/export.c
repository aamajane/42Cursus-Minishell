/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:12:22 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/13 17:20:30 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_export(char **args, int outfd)
{
	char	*var_name;
	int		i;

	g_data.exit_code = 0;
	if (!args[0])
		return (print_export(outfd));
	if (!args[0][0])
		return (print_variable_name_error("export", "`'"));
	i = -1;
	while (args[++i])
	{
		var_name = get_export_variable_name(args[i]);
		if (check_variable_name(var_name))
		{
			if (ft_strchr(args[i], '='))
				export_variable(&g_data.env, args[i]);
			export_variable(&g_data.exp, args[i]);
		}
		else
			print_variable_name_error("export", args[i]);
		free(var_name);
	}
}

void	print_export(int outfd)
{
	int	i;

	sort_export();
	i = 0;
	while (g_data.exp[i])
	{
		ft_putstr_fd("declare -x ", outfd);
		ft_putstr_fd(g_data.exp[i++], outfd);
		ft_putstr_fd("\n", outfd);
	}
}

void	sort_export(void)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (g_data.exp[++i])
	{
		j = -1;
		while (g_data.exp[++j])
		{
			if (ft_strncmp(g_data.exp[i], g_data.exp[j], \
							ft_strlen(g_data.exp[i])) < 0)
			{
				tmp = g_data.exp[i];
				g_data.exp[i] = g_data.exp[j];
				g_data.exp[j] = tmp;
			}
		}
	}
}

void	export_variable(char ***env, char *arg)
{
	t_exp	exp;

	exp.var = get_export_full_variable(arg);
	exp.var_name = get_export_variable_name(arg);
	if (get_variable_value(*env, exp.var_name))
	{
		exp.index = get_variable_index(*env, exp.var_name);
		if (!join_export_plus_variable_value(*env + exp.index, arg))
		{
			free((*env)[exp.index]);
			(*env)[exp.index] = ft_strdup(exp.var);
		}
	}
	else
	{
		exp.new_env = duplicate_env(*env);
		exp.len = double_pointer_length(*env);
		if (!add_export_plus_variable(&exp.new_env[exp.len], arg))
			exp.new_env[exp.len] = ft_strdup(exp.var);
		exp.new_env[exp.len + 1] = NULL;
		free_double_pointer(*env);
		(*env) = exp.new_env;
	}
	free(exp.var);
	free(exp.var_name);
}
