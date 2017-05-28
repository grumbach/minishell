/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 00:17:16 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/28 09:20:03 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			// ft_printf("i = %d\n", i);
			if (comp > 0)
				i += (BUILT_IN_CMD_NB - i + 1) / 2;
			else
				i -= (i + 1) / 2;
		}
		else
			return (cmd[i].cmd(args, envp));
	return (0);
}

static int	command_center(t_cmd *cmd, char *line, char **envp)
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
		if (!mini_exec(line, args, envp))
			shell_error(3, line);
	return (1);
}

static int	get_actions(char buf)
{
	ft_printf("{%c}", buf);
	if (buf == '\t')
		return (1);
	return (0);
}

void		mini_parse(t_array *line, t_cmd *cmd, char **envp)
{
	int		ret;
	int		index;
	char	buf;

	index = 0;
	while ((ret = read(0, &buf, 1)))
		if (ret == -1)
			errors(1, "failed to read");
		else if (buf == '\n')
		{
			if (!(line = ft_arrayadd(line, (char[1]){'\0'}, index, 1)))
				errors(0, "malloc failed");
			if (!command_center(cmd, line->content, envp))
				break ;
			index = 0;
			ft_printf("$> ");
			continue ;
		}
		else if (get_actions(buf))
			continue ;
		else if ((!((!index && buf == SEPARATOR_CHAR) || \
			(index && buf == SEPARATOR_CHAR && \
			((char*)line->content)[index - 1] == SEPARATOR_CHAR))) && \
			(!(line = ft_arrayadd(line, (char[1]){buf}, index++, 1))))
				errors(0, "malloc failed");
}
