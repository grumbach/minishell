/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 13:45:07 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/28 19:16:05 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long		errors(const int erno, const char *comment, t_env **env)
{
	ft_putstr_fd("minishell: ", 2);
	if (comment)
		ft_putendl_fd(comment, 2);
	if (erno == 0)
		ft_putstr_fd("System Failure\n", 2);
	if (erno == 1)
		ft_putstr_fd("The Blood Moon is rising...\n", 2);
	mini_free_env(env, NULL);
	exit(EXIT_FAILURE);
}

long		shell_error(const int erno, const char *comment)
{
	ft_putstr_fd("minishell: ", 2);
	if (comment)
		ft_putstr_fd(comment, 2);
	if (erno == 2)
		ft_putstr_fd(" : Permission denied\n", 2);
	if (erno == 3)
		ft_putstr_fd(" : command not found\n", 2);
	if (erno == 4)
		ft_putstr_fd("A computer is like air conditioning,\n"
		"      It becomes useless when you open Windows.\n"
		"                                 Linus Torvalds\n", 2);
	if (erno == 5)
		ft_putstr_fd(" not set\n", 2);
	if (erno == 6)
		ft_putstr_fd(" : something else....\n", 2);
	return (0);
}
