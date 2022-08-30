/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:57:40 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/14 12:11:58 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_variable(char **exp_arg, char *str, int *i, int *j)
{
	char	*var;
	char	*var_name;
	char	*var_val;

	(*j)++;
	if (ft_isalpha(str[*j]) || str[*j] == '_')
	{
		var = get_variable_name(str + *j, j);
		var_name = ft_strjoin(var, "=");
		var_val = get_variable_value(g_data.env, var_name);
		free(var);
		free(var_name);
		if (var_val && *var_val)
			join_expanded_variable(exp_arg, var_val, i);
	}
	else if (str[*j] == '?')
	{
		(*j)++;
		var_val = ft_itoa(g_data.exit_code);
		join_expanded_variable(exp_arg, var_val, i);
		free(var_val);
	}
}

char	*get_variable_name(char *str, int *j)
{
	char	*var_name;
	int		var_len;
	int		i;

	var_len = get_variable_name_len(str);
	var_name = (char *)malloc(sizeof(char) * (var_len + 1));
	if (!var_name)
		exit(puterror("Malloc Error"));
	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
	{
		var_name[i] = str[i];
		i++;
	}
	var_name[i] = '\0';
	*j += var_len;
	return (var_name);
}

int	get_variable_name_len(char *str)
{
	int	i;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i);
}

void	join_expanded_variable(char **exp_arg, char *var_val, int *i)
{
	char	*join_cmd;

	(*exp_arg)[*i] = '\0';
	join_cmd = ft_strjoin(*exp_arg, var_val);
	*i = ft_strlen(join_cmd);
	free(*exp_arg);
	*exp_arg = join_cmd;
}
