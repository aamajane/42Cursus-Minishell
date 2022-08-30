/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:55:55 by aamajane          #+#    #+#             */
/*   Updated: 2021/11/11 16:57:58 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (start >= i)
		dst = (char *)malloc(sizeof(*dst));
	else if (i - start < len)
		dst = (char *)malloc(sizeof(*dst) * (i - start + 1));
	else
		dst = (char *)malloc(sizeof(*dst) * (len + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (s[start] && i < len && start < ft_strlen(s))
		dst[i++] = s[start++];
	dst[i] = '\0';
	return (dst);
}
