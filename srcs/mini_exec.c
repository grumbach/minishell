/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 00:16:00 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/28 09:09:49 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd(const char *path, char *const *args, char *const *envp)
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

static char	*whereis_command(char *command, char **envp)
{
	char	*path;

	if (1)//found!
	{
		if (!(path = ft_strjoin(*envp, command)))
			errors(0, "malloc failed");
		return (path);
	}
	return (0);
}

int			mini_exec(char *command, char *args, char **envp)
{
	char	*path;

	if (!(path = whereis_command(command, envp)))
		return (0);
	//set args
	exec_cmd(path, &args, envp);//
	free(path);
	return (1);
}

// char		*locate_in_env(const char *var, const char **envp)
// {
// 	if (!envp)
// 		return (NULL);
// 	while (*envp)
// 	{
// 		ft_printf("%s\n", env);
// 		(*envp)++;
// 	}
// }
