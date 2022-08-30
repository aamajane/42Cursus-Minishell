/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:26:26 by aamajane          #+#    #+#             */
/*   Updated: 2021/11/06 13:26:29 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(src);
	dup = (char *)malloc(sizeof(*dup) * (len + 1));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, src, len + 1);
	return (dup);
}
