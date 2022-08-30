/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:16:52 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/13 14:05:46 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_spaces(char ***full_cmds)
{
	char	*sp_cmd;
	int		sp_count;
	int		i;

	i = 0;
	while ((*full_cmds)[i])
	{
		sp_count = added_spaces_count((*full_cmds)[i]);
		if (sp_count)
		{
			sp_cmd = copy_command_with_spaces((*full_cmds)[i], sp_count);
			free((*full_cmds)[i]);
			(*full_cmds)[i] = sp_cmd;
		}
		i++;
	}
}

int	added_spaces_count(char *cmd)
{
	int	sp_count;
	int	i;

	sp_count = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<' || cmd[i] == '>')
		{
			if (cmd[i + 1] != '<' && cmd[i + 1] != '>' && cmd[i + 1] != ' ')
				sp_count++;
			if (i && \
				cmd[i - 1] != '<' && cmd[i - 1] != '>' && cmd[i - 1] != ' ')
				sp_count++;
		}
		i += skip_quotes_content(cmd + i);
		if (cmd[i])
			i++;
	}
	return (sp_count);
}

char	*copy_command_with_spaces(char *cmd, int spaces_count)
{
	char	*sp_cmd;
	int		cmd_len;
	int		i;
	int		j;

	cmd_len = ft_strlen(cmd) + spaces_count;
	sp_cmd = (char *)malloc(sizeof(char) * (cmd_len + 1));
	if (!sp_cmd)
		exit(puterror("Malloc Error"));
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<' || cmd[i] == '>')
			copy_spaces(&sp_cmd, cmd, &j, &i);
		else if (cmd[i] && !copy_quotes_content(&sp_cmd, cmd, &j, &i))
			sp_cmd[j++] = cmd[i++];
	}
	sp_cmd[j] = '\0';
	return (sp_cmd);
}

void	copy_spaces(char **sp_cmd, char *cmd, int *j, int *i)
{
	if (*i && \
		cmd[*i - 1] != '<' && cmd[*i - 1] != '>' && cmd[*i - 1] != ' ')
		(*sp_cmd)[(*j)++] = ' ';
	(*sp_cmd)[(*j)++] = cmd[*i];
	if (cmd[*i + 1] != '<' && cmd[*i + 1] != '>' && cmd[*i + 1] != ' ')
		(*sp_cmd)[(*j)++] = ' ';
	(*i)++;
}

int	copy_quotes_content(char **sp_cmd, char *cmd, int *j, int *i)
{
	char	quote;

	if (cmd[*i] == 34 || cmd[*i] == 39)
	{
		quote = cmd[(*i)];
		(*sp_cmd)[(*j)++] = cmd[(*i)++];
		while (cmd[*i] && cmd[*i] != quote)
			(*sp_cmd)[(*j)++] = cmd[(*i)++];
		if (cmd[*i] == quote)
			(*sp_cmd)[(*j)++] = cmd[(*i)++];
		return (1);
	}
	return (0);
}
