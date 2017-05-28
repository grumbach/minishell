/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 00:21:41 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/28 07:27:55 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			mini_cd(char *args, char **envp)
{
	ft_printf("called cd\n");
	(void)envp;
	if (!args)
	{
		chdir("~");
		return (1);
	}
	while (*args == SEPARATOR_CHAR)
		args++;
	if (*args == '-' && !*(args + 1))
		chdir("..");//LASTDIR!!
	if (chdir(args) == -1)
		shell_error(2, args);
	return (1);
}

int			mini_echo(char *args, char **envp)
{
	ft_printf("%s\n", args);
	(void)envp;
	return (1);
}

int			mini_env(char *args, char **envp)
{
	(void)args;
	if (!envp)
		return (0);
	while (*envp)
	{
		ft_printf("%s\n", *envp);
		envp++;
	}
	return (1);
}

int			mini_setenv(char *args, char **envp)
{
	ft_printf("called setenv\n");
	(void)args;
	(void)envp;
	return (1);
}

int			mini_unsetenv(char *args, char **envp)
{
	ft_printf("called unsetenv\n");
	(void)args;
	(void)envp;
	return (1);
}
