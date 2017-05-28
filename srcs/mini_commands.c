/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 00:21:41 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/28 03:14:26 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			mini_cd(char *args, char **envp)
{
	ft_printf("called cd\n");
	(void)args;
	(void)envp;
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
	// int		i;
	//
	// i = 0;
	// while (envp[i])
	// {
	// 	ft_printf("%s\n", *envp);
	// 	++;
	// }
	ft_printf("called env\n");
	(void)args;
	(void)envp;
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
