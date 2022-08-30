/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections_syntax.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:51:36 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/10 15:53:17 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_redirections_syntax(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strncmp(line + i, "<<", 2) || !ft_strncmp(line + i, ">>", 2) || \
			line[i] == '<' || line[i] == '>')
		{
			i++;
			if (line[i] == '<' || line[i] == '>')
				i++;
			while (line[i] == ' ')
				i++;
			if (!line[i] || line[i] == '>' || line[i] == '<' || line[i] == '|')
				return (print_syntax_error("redirection"));
		}
		i += skip_quotes_content(line + i);
		if (line[i])
			i++;
	}
	if (!check_after_redirections(line))
		return (0);
	return (1);
}

int	check_after_redirections(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			while (ft_isdigit(line[i + 1]))
			{
				i++;
				if (line[i + 1] == '<' || line[i + 1] == '>')
					return (print_syntax_error("redirection"));
			}
		}
		i += skip_quotes_content(line + i);
		if (line[i])
			i++;
	}
	return (1);
}
