/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:51:15 by aamajane          #+#    #+#             */
/*   Updated: 2021/11/11 10:10:47 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int n, unsigned int nb)
{
	int	i;

	i = 1;
	while (nb >= 10)
	{
		nb /= 10;
		i++;
	}
	if (n < 0)
		i++;
	return (i);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	char			*dst;
	int				len;

	if (n < 0)
		nb = -n;
	else
		nb = n;
	len = ft_nbrlen(n, nb);
	dst = (char *)malloc(sizeof(*dst) * (len + 1));
	if (!dst)
		return (NULL);
	dst[len--] = '\0';
	while (len >= 0)
	{
		dst[len--] = nb % 10 + '0';
		nb /= 10;
	}
	if (n < 0)
		dst[0] = '-';
	return (dst);
}
