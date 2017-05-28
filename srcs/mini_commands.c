/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 00:21:41 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/28 19:34:05 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			mini_env(char *args, t_env **env)
{
	(void)args;
	if (!(*env))
		return (0);
	while (*env)
	{
		ft_printf("%s\n", (*env)->content);
		(*env) = (*env)->next;
	}
	return (1);
}

int			mini_setenv(char *args, t_env **env)
{
	char	*word;
	char	*who;
	t_env	*new;

	if (!args)
		shell_error(1, "setenv : \nusage : unsetenv [ENV_VAR]=\"[string]\"\n");
	word = args;
	while (*args && *args != '=')
		args++;
	if (*args == '=')
		*args++ = '\0';
	if ((who = mini_whereis_env(args, *env)))
		mini_free_env(env, who);
	mini_unsetenv(word, env);
	if (!(new = ft_memalloc(sizeof(t_env))) ||
		!(new->content = ft_strdup(args)))
		errors(0, "malloc failed", env);
	while (*env)
		env = &(*env)->next;
	*env = new;
	mini_env(args, env);
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

int			mini_cd(char *args, t_env **env)
{
	int		i;
	char	*who;

	if (!args && !(who = mini_whereis_env("HOME", *env)))
		return (shell_error(5, "HOME"));//TODO smth else here
	if (args)
	{
		i = 0;
		while (args[i] && args[i] != SEPARATOR_CHAR)
			i++;
		args[i] = '\0';
		if (*args == '-' && !*(args + 1))
		{
			if (!(who = mini_whereis_env("OLDPWD", *env)))
				return (shell_error(5, "OLDPWD"));
		}
		else
			who = args;
	}
	if (chdir(who) == -1)
		shell_error(2, args);
	// mini_setenv("PWD", );
	// mini_setenv("OLDPWD", ); //TODO OLDPWD PWD update!!
	return (1);
}

int			mini_echo(char *args, t_env **env)
{
	char	*who;
	char	*word;

	while (args && *args)
	{
		word = args;
		while (*args && *args != SEPARATOR_CHAR)
			args++;
		if (*args)
		{
			*args = '\0';
			args++;
		}
		if ((who = mini_whereis_env(word, *env)))
			ft_printf("%s", who + ft_strlen(word) + 1);
		else if (word)
			ft_printf("%s", word);
		if (*args)
			ft_printf(" ");
	}
	ft_printf("\n");
	return (1);
}
