/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 00:21:41 by agrumbac          #+#    #+#             */
/*   Updated: 2017/06/01 05:06:21 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			mini_setenv(char *args, t_env **env)
{
	char	*var;

	if (!args)
		return (shell_error(1, "setenv : \nusage : setenv " \
		"[ENV_VAR]=[string]\n"));
	var = args;
	while (*args && *args != '=')
		args++;
	if (*args != '=' || args == var)
		return (shell_error(1, "setenv : bad synthax\n"));
	*args++ = '\0';
	mini_set_env(var, args, env);
	mini_env(0, env);
	return (1);
}

int			mini_unsetenv(char *args, t_env **env)
{
	char	*who;

	if (!args)
		return (shell_error(1, "unsetenv : \nusage : unsetenv [ENV_VAR]\n"));
	if (!(who = mini_whereis_env(args, *env)))
		return (shell_error(5, args));
	mini_free_env(env, who);
	mini_env(args, env);
	return (1);
}

int			mini_env(char *args, t_env **env)
{
	t_env	*see;

	(void)args;
	if (!env || !(*env))
		return (0);
	see = *env;
	while (see)
	{
		ft_printf("%s\n", see->content);
	 	see = see->next;
	}
	return (1);
}

int			mini_cd(char *args, t_env **env)
{
	char	path[MAXPATHLEN + 1];
	char	*who;

	if (!args)
	{
		if (!(who = mini_whereis_env("HOME", *env)))
			return (shell_error(5, "HOME"));
		who += ft_strlen("HOME=");
	}
	else if (*args == '-' && !*(args + 1))
	{
		if (!(who = mini_whereis_env("OLDPWD", *env)))
			return (shell_error(5, "OLDPWD"));
		who += ft_strlen("OLDPWD=");
	}
	else
		who = args;
	if (!(getcwd(path, MAXPATHLEN)))
		return (shell_error(5, "current working directory"));
	if (chdir(who) == -1)
		return (shell_error(2, "cd"));
	mini_set_env("OLDPWD", path, env);
	if (!(getcwd(path, MAXPATHLEN)))
		return (shell_error(5, "current working directory"));
	return (mini_set_env("PWD", path, env));
}
