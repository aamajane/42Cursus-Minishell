/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:49:27 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/14 11:27:15 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_export_variable_name(char *arg)
{
	t_exp	exp;

	if (*arg == '=')
		return (ft_strdup(arg));
	exp.array = ft_split(arg, '=');
	if (!exp.array)
		exit(puterror("Split Error"));
	exp.var_name = ft_strdup(exp.array[0]);
	exp.len = ft_strlen(exp.var_name);
	if (exp.var_name[exp.len - 1] == '+')
		exp.var_name[exp.len - 1] = '\0';
	free_double_pointer(exp.array);
	return (exp.var_name);
}

char	*get_export_full_variable(char *arg)
{
	char	*var;

	if (!ft_strchr(arg, '='))
		var = ft_strjoin(arg, "=");
	else
		var = ft_strdup(arg);
	return (var);
}

int	join_export_plus_variable_value(char **new_var, char *arg)
{
	t_exp	exp;

	exp.array = ft_split(arg, '=');
	if (!exp.array)
		exit(puterror("Split Error"));
	exp.len = ft_strlen(exp.array[0]);
	if (exp.array[0][exp.len - 1] == '+')
	{
		exp.i = 0;
		while (arg[exp.i] && arg[exp.i] != '=')
			exp.i++;
		if (arg[exp.i] == '=')
			exp.i++;
		exp.tmp = *new_var;
		*new_var = ft_strjoin(exp.tmp, arg + exp.i);
		free(exp.tmp);
		free_double_pointer(exp.array);
		return (1);
	}
	free_double_pointer(exp.array);
	return (0);
}

int	add_export_plus_variable(char **new_var, char *arg)
{
	t_exp	exp;

	exp.array = ft_split(arg, '=');
	if (!exp.array)
		exit(puterror("Split Error"));
	exp.len = ft_strlen(exp.array[0]);
	if (exp.array[0][exp.len - 1] == '+')
	{
		*new_var = (char *)malloc(sizeof(char) * (ft_strlen(arg) + 1));
		if (!*new_var)
			exit(puterror("Malloc Error"));
		exp.i = 0;
		exp.j = 0;
		while (arg[exp.i] && arg[exp.i] != '+')
			(*new_var)[exp.j++] = arg[exp.i++];
		if (arg[exp.i] == '+')
			exp.i++;
		while (arg[exp.i])
			(*new_var)[exp.j++] = arg[exp.i++];
		(*new_var)[exp.j] = '\0';
		free_double_pointer(exp.array);
		return (1);
	}
	free_double_pointer(exp.array);
	return (0);
}
