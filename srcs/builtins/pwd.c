/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:12:32 by aamajane          #+#    #+#             */
/*   Updated: 2022/06/13 17:20:53 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_pwd(char **args, int outfd)
{
	char	*cwd;

	g_data.exit_code = 0;
	if (args[0])
		if (args[0][0] == '-' && args[0][1])
			return (print_pwd_error(args[0][1]));
	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, outfd);
	ft_putstr_fd("\n", outfd);
	free(cwd);
}
