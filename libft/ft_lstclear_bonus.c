/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:15:15 by aamajane          #+#    #+#             */
/*   Updated: 2021/11/11 18:04:37 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next_elm;

	if (!*lst)
		return ;
	while (*lst)
	{
		next_elm = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next_elm;
	}
	*lst = NULL;
}
