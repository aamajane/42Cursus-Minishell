/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:51:16 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/10 15:52:22 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_pipes_syntax(char *line)
{
	int	i;

	if (!check_first_pipe(line))
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
		{
			i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == '|')
				return (print_syntax_error("pipe"));
		}
		i += skip_quotes_content(line + i);
		if (line[i])
			i++;
	}
	return (1);
}

int	check_first_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '|')
		return (print_syntax_error("pipe"));
	return (1);
}
