/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 00:21:41 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/29 22:54:54 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_env(char *var, char *content, t_env **env)
{
	char 	*who;
	t_env	*new;

	if ((who = mini_whereis_env(var, *env)))
		mini_free_env(env, who);
	if (!(new = ft_memalloc(sizeof(t_env))) ||
		!(new->content = ft_strnjoin(3, var, "=", content)))
		return (errors(0, "malloc failed", env));
	while (*env)
		env = &(*env)->next;
	*env = new;
	return (1);
}

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
	set_env(var, args, env);
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
	set_env("OLDPWD", path, env);
	if (!(getcwd(path, MAXPATHLEN)))
		return (shell_error(5, "current working directory"));
	return (set_env("PWD", path, env));
}
