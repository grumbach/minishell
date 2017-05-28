/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_commands2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 06:12:44 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/28 19:06:29 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				mini_pwd(char *args, t_env **env)
{
	char		buf[MAXPATHLEN + 1];

	(void)args;
	(void)env;
	ft_bzero(&buf, sizeof(buf));
	if (!(getcwd(buf, MAXPATHLEN)))
		shell_error(2, "pwd");
	ft_printf("%s\n", buf);
	return (1);
}

char			*mini_whereis_env(char *envvar, t_env *env)
{
	size_t		len;

	len = ft_strlen(envvar);
	while (env)
	{
		if (!ft_strncmp(envvar, env->content, len) && \
			env->content[len] == '=')
			return (env->content);
		env = env->next;
	}
	return (NULL);
}
