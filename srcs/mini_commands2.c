/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_commands2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 06:12:44 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/31 19:16:58 by agrumbac         ###   ########.fr       */
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
