/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 05:41:32 by agrumbac          #+#    #+#             */
/*   Updated: 2017/06/01 15:15:37 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_builtin(t_cmd *cmd, char *command, char *args, t_env **env)
{
	int		i;
	int		n;
	int		comp;

	n = BUILT_IN_CMD_NB;
	i = BUILT_IN_CMD_NB / 2;
	while (i >= 0 && i < BUILT_IN_CMD_NB && --n)
		if ((comp = ft_strcmp(command, cmd[i].name)))
		{
			if (comp > 0)
				i += (BUILT_IN_CMD_NB - i + 1) / 2;
			else
				i -= (i + 1) / 2;
		}
		else
		{
			cmd[i].cmd(args, env);
			return (1);
		}
	return (0);
}

int			mini_command(t_cmd *cmd, char *line, t_env **env)
{
	int		i;
	char	*args;

	if (ft_strequ(line, "exit"))
		return (0);
	if (ft_strequ(line, "windows"))
		shell_error(4, 0);
	i = 0;
	args = NULL;
	if (!*line)
		return (1);
	while (line[i] && line[i] != SEPARATOR_CHAR)
		i++;
	if (line[i])
	{
		line[i] = '\0';
		args = &line[i + 1];
		while (*args == SEPARATOR_CHAR)
			args++;
		args = *args ? args : NULL;
	}
	if (!exec_builtin(cmd, line, args, env))
		mini_exec(line, args, *env);
	return (1);
}
