/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:04:33 by aamajane          #+#    #+#             */
/*   Updated: 2021/11/11 10:25:09 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_wordcount(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		i = ft_wordlen(s, c);
		s += i;
		if (i)
			count++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	int		count;
	int		len;
	int		i;

	if (!s)
		return (NULL);
	count = ft_wordcount(s, c);
	dst = (char **)malloc(sizeof(*dst) * (count + 1));
	if (!dst)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		while (*s == c)
			s++;
		len = ft_wordlen(s, c);
		dst[i] = (char *)malloc(sizeof(**dst) * (len + 1));
		if (!dst[i])
			return (NULL);
		ft_strlcpy(dst[i], s, len + 1);
		s += len;
	}
	dst[i] = 0;
	return (dst);
}
