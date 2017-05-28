/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 00:21:41 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/28 22:26:16 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_env(char *var, char *content, t_env **env)
{
	char 	*who;
	t_env	*new;

	if ((who = mini_whereis_env(var, *env)))
		mini_free_env(env, who);
	if (!(new = ft_memalloc(sizeof(t_env))) ||
		!(new->content = ft_strnjoin(3, var, "=", content)))
		errors(0, "malloc failed", env);
	while (*env)
		env = &(*env)->next;
	*env = new;
}

int			mini_setenv(char *args, t_env **env)
{
	char	*var;

	if (!args)
		shell_error(1, "setenv : \nusage : unsetenv [ENV_VAR]=[string]\n");
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
		shell_error(1, "unsetenv : \nusage : unsetenv [ENV_VAR]\n");
	if (!(who = mini_whereis_env(args, *env)))
		return (shell_error(5, args));
	mini_free_env(env, who);
	mini_env(args, env);
	return (1);
}

int			mini_env(char *args, t_env **env)
{
	t_env	*see;

	see = *env;
	(void)args;
	if (!see)
		return (0);
	while (see)
	{
		ft_printf("%s\n", see->content);
	 	see = see->next;
	}
	return (1);
}

int			mini_cd(char *args, t_env **env)
{
	int		i;
	char	*who;
	char	*old;

	if (!args && !(who = mini_whereis_env("HOME", *env)))
		return (shell_error(5, "HOME"));//TODO smth else here
	if (args)
	{
		i = 0;
		while (args[i] && args[i] != SEPARATOR_CHAR)
			i++;
		args[i] = '\0';
		if ((*args == '-' && !*(args + 1)) && \
			!(who = mini_whereis_env("OLDPWD", *env)))
			return (shell_error(5, "OLDPWD"));
		else if (!(*args == '-' && !*(args + 1)))
			who = args;
	}
	if (chdir(who) == -1)
		shell_error(2, args);
	old = mini_whereis_env("PWD", *env);
	set_env("PWD", who, env);
	set_env("OLDPWD", old + ft_strlen("PWD="), env);//TODO fix this!!!
	return (1);
}
