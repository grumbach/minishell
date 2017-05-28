/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 00:17:16 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/28 06:32:26 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*whereis_command(char *command, char **envp)
{
	char	*path;

	if (1)//found!
	{
		if (!(path = ft_strjoin(*envp, command)))
			errors(0, "malloc failed");
		return (path);
	}
	return (0);
}

static int	exec_path(char *command, char *args, char **envp)
{
	char	*path;

	if (!(path = whereis_command(command, envp)))
		return (0);
	//set args
	mini_exec(path, &args, envp);//
	free(path);
	return (1);
}

static int	exec_builtin(t_cmd *cmd, char *command, char *args, char **envp)
{
	int		i;
	int		n;
	int		comp;

	n = BUILT_IN_CMD_NB;
	i = BUILT_IN_CMD_NB / 2;
	while (i >= 0 && i < BUILT_IN_CMD_NB && --n)
		if ((comp = ft_strcmp(command, cmd[i].name)))
		{
			ft_printf("i = %d\n", i);
			if (comp > 0)
				i += (BUILT_IN_CMD_NB - i) / 2;
			else
				i -= (i + 1) / 2;
		}
		else
			return (cmd[i].cmd(args, envp));
	return (0);
}

int			mini_parse(t_cmd *cmd, char *line, char **envp)
{
	int		i;
	char	*args;

	if (ft_strequ(line, "exit"))
		return (0);
	if (ft_strequ(line, "windows"))
		shell_error(4, 0);
	i = 0;
	args = NULL;
	while (line[i] && line[i] != SEPARATOR_CHAR)
		i++;
	if (line[i])
	{
		line[i] = '\0';
		args = &line[i + 1];
	}
	if (!exec_builtin(cmd, line, args, envp))
		if (!exec_path(line, args, envp))
			shell_error(3, line);
	return (1);
}
