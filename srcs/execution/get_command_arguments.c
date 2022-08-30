/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_arguments.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:59:02 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/02 20:10:45 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_command_arguments(char **full_cmd)
{
	char	**args;
	int		args_count;
	int		i;
	int		j;

	args_count = arguments_count(full_cmd);
	if (!args_count)
		return (NULL);
	args = (char **)malloc(sizeof(char *) * (args_count + 1));
	if (!args)
		exit(puterror("Malloc Error"));
	i = 0;
	j = 0;
	while (full_cmd[i])
	{
		if (is_not_argument(full_cmd, i))
			i += 2;
		else if (full_cmd[i])
			args[j++] = ft_strdup(full_cmd[i++]);
	}
	args[j] = NULL;
	return (args);
}

int	arguments_count(char **full_cmd)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (full_cmd[i])
	{
		if (is_not_argument(full_cmd, i))
			i += 2;
		else if (full_cmd[i])
		{
			count++;
			i++;
		}
	}
	return (count);
}

int	is_not_argument(char **full_cmd, int i)
{
	if ((!ft_strncmp(full_cmd[i], "<<", ft_strlen(full_cmd[i]) + 1) || \
		!ft_strncmp(full_cmd[i], ">>", ft_strlen(full_cmd[i]) + 1) || \
		!ft_strncmp(full_cmd[i], "<", ft_strlen(full_cmd[i]) + 1) || \
		!ft_strncmp(full_cmd[i], ">", ft_strlen(full_cmd[i]) + 1)) && \
		full_cmd[i + 1])
		return (1);
	return (0);
}
