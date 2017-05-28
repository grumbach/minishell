/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 00:16:00 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/28 01:08:52 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		mini_exec(const char *path, char *const *args, char *const *envp)
{
	pid_t	pid;

	if ((pid = fork()) == -1)
		errors(0, "fork error");
	if (!pid)
	{
		if (execve(path, args, envp) == -1)
			errors(0, "execve error");
		exit(EXIT_SUCCESS);
	}
	else if (wait(NULL) == -1)
		errors(0, "wait error");
}
