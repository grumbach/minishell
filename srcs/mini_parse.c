/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 00:17:16 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/28 04:52:15 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_builtin(t_cmd *cmd, char *line, char **envp)
{
	int		i;
	int		comp;
	char	*args;

	i = 0;
	args = NULL;
	while (line[i] && line[i] != SEPARATOR_CHAR)
		i++;
	if (line[i])
	{
		line[i] = '\0';
		args = &line[i + 1];
	}
	i = BUILT_IN_CMD_NB / 2;
	while (i >= 0 && i < BUILT_IN_CMD_NB)
		if ((comp = ft_strcmp(line, cmd[i].name)))
		{
			ft_printf("i = %d\n", i);
			if (comp > 0)
				i += (BUILT_IN_CMD_NB - i) / 2;
			else
				i -= (i + 1) / 2;
		}
		else
			return (cmd[i].cmd(args, envp)); //must return 1
	return (0);
}

static int	exec_path(char *line, char **envp)
{
	mini_exec(line, envp, envp);
	return (0);
}

int			mini_parse(t_cmd *cmd, char *line, char **envp)
{
	if (ft_strequ(line, "exit"))
		return (0);
	if (ft_strequ(line, "windows"))
		shell_error(4, 0);
	if (!exec_builtin(cmd, line, envp))
		if (!exec_path(line, envp))
			shell_error(1, line);
	return (1);
}
