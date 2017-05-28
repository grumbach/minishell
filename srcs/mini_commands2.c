/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_commands2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 06:12:44 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/28 18:01:53 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				mini_pwd(char *args, t_env *env)
{
	char		buf[MAXPATHLEN + 1];

	(void)args;
	(void)env;
	ft_bzero(&buf, sizeof(buf));
	if (!(getcwd(buf, MAXPATHLEN)))
		shell_error(1, "Permission Denied\n");
	ft_printf("%s\n", buf);
	return (1);
}

char			*mini_whereis_env(char *envvar, t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(envvar, env->content, ft_strlen(envvar)))
			return (env->content);
		env = env->next;
	}
	return (NULL);
}
