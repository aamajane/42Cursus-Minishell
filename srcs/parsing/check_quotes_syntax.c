/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes_syntax.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:28:32 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/10 15:50:57 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quotes_syntax(char *line)
{
	char	quote;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] != quote)
				return (print_syntax_error("quote"));
		}
		if (line[i])
			i++;
	}
	return (1);
}

int	skip_quotes_content(char *line)
{
	char	quote;
	int		i;

	i = 0;
	if (line[i] == 34 || line[i] == 39)
	{
		quote = line[i++];
		while (line[i] && line[i] != quote)
			i++;
	}
	return (i);
}
