/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 00:21:41 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/28 16:20:21 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			mini_cd(char *args, t_env *env)
{
	ft_printf("called cd\n");
	(void)env;
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

int			mini_echo(char *args, t_env *env)
{
	(void)env;
	ft_printf("%s\n", args);
	return (1);
}

int			mini_env(char *args, t_env *env)
{
	(void)args;
	if (!env)
		return (0);
	while (env)
	{
		ft_printf("%s\n", env->content);
		env = env->next;
	}
	return (1);
}

int			mini_setenv(char *args, t_env *env)
{
	ft_printf("called setenv\n");
	(void)args;
	(void)env;
	return (1);
}

int			mini_unsetenv(char *args, t_env *env)
{
	ft_printf("called unsetenv\n");
	(void)args;
	(void)env;
	return (1);
}
