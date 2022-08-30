/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_remove_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:56:27 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/14 12:11:48 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_and_remove_quotes(char *str)
{
	char	*exp_arg;
	int		i;
	int		j;

	exp_arg = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!exp_arg)
		exit(puterror("Malloc Error"));
	i = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] == '$' && (ft_isalpha(str[j + 1]) || \
			str[j + 1] == '_' || str[j + 1] == '?'))
			expand_variable(&exp_arg, str, &i, &j);
		else if (str[j] == 39)
			remove_single_quote(&exp_arg, str, &i, &j);
		else if (str[j] == 34)
			remove_double_quote(&exp_arg, str, &i, &j);
		else
			duplicate_argument(&exp_arg, str, &i, &j);
	}
	exp_arg[i] = '\0';
	check_expanded_argument(&exp_arg, str, i);
	return (exp_arg);
}

void	remove_single_quote(char **exp_arg, char *str, int *i, int *j)
{
	(*j)++;
	while (str[*j] && str[*j] != 39)
		(*exp_arg)[(*i)++] = str[(*j)++];
	if (str[*j])
		(*j)++;
}

void	remove_double_quote(char **exp_arg, char *str, int *i, int *j)
{
	(*j)++;
	while (str[*j] && str[*j] != 34)
	{
		if (str[*j] == '$' && (ft_isalpha(str[*j + 1]) || \
			str[*j + 1] == '_' || str[*j + 1] == '?'))
			expand_variable(exp_arg, str, i, j);
		else
			duplicate_argument(exp_arg, str, i, j);
	}
	if (str[*j])
		(*j)++;
}

void	duplicate_argument(char **exp_arg, char *str, int *i, int *j)
{
	char	*tmp;
	int		len;

	(*exp_arg)[(*i)++] = '\0';
	len = ft_strlen(*exp_arg);
	tmp = (char *)malloc(sizeof(char) * (len + 5));
	if (!tmp)
		exit(puterror("Malloc Error"));
	ft_strlcpy(tmp, *exp_arg, len + 1);
	tmp[len] = str[(*j)++];
	free(*exp_arg);
	*exp_arg = tmp;
}

void	check_expanded_argument(char **exp_arg, char *str, int i)
{
	if (i == 0 && !ft_strchr(str, 34) && !ft_strchr(str, 39))
	{
		free(*exp_arg);
		*exp_arg = NULL;
	}
}
