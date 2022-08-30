/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_variable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:22:29 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/14 12:21:48 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_delimiter_qoute(char **str)
{
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == 34 || (*str)[i] == 39)
		{
			if (i && (*str)[i - 1] == '$')
				j--;
			quote = (*str)[i++];
			while ((*str)[i] && (*str)[i] != quote)
				(*str)[j++] = (*str)[i++];
			if ((*str)[i] == quote)
				i++;
		}
		else
			(*str)[j++] = (*str)[i++];
	}
	(*str)[j] = '\0';
}

void	expand_heredoc_variable(char **line)
{
	char	*new_line;
	int		i;
	int		j;

	new_line = (char *)malloc(sizeof(char) * (ft_strlen(*line) + 1));
	if (!new_line)
		exit(puterror("Malloc Error"));
	i = 0;
	j = 0;
	while ((*line)[j])
	{
		if ((*line)[j] == '$' && (ft_isalpha((*line)[j + 1]) || \
			(*line)[j + 1] == '_' || (*line)[j + 1] == '?'))
			expand_variable(&new_line, *line, &i, &j);
		else
			duplicate_argument(&new_line, *line, &i, &j);
	}
	new_line[i] = '\0';
	free(*line);
	*line = new_line;
}
