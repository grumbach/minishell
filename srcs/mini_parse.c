/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 00:17:16 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/29 22:50:23 by agrumbac         ###   ########.fr       */
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

static int	command_center(t_cmd *cmd, char *line, t_env **env)
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
		if (!mini_exec(line, args, *env))
			shell_error(3, line);
	return (1);
}

static int	get_termcaps(const int buf)
{
	//TODO
	if (ft_isprint(buf))
		write(0, &buf, 1);
	else
		ft_printf("[%d]\n", buf);
	return (0);
}

static int	print_prompt(void)
{
	char	buf[MAXPATHLEN + 1];

	if (!(getcwd(buf, MAXPATHLEN)))
		shell_error(5, "current working directory");
	ft_printf("%s[%s]%s$>%s ", BLUE, buf, GREEN, NORMAL);
	return (0);
}

void		mini_parse(t_array *line, t_cmd *cmd, t_env **env)
{
	int		ret;
	int		index;
	int		buf;

	buf = 0;
	index = print_prompt();
	while (buf != 4 && (ret = read(0, &buf, 4)))
		if (ret == -1)
			errors(1, "failed to read", env);
		else if ((char)buf == '\n' && write(0, &buf, 1))
		{
			if (!(line = ft_arrayadd(line, (char[1]){'\0'}, index, 1)))
				errors(0, "malloc failed", env);
			if (!command_center(cmd, line->content, env))
				break ;
			index = print_prompt();
			continue ;
		}
		else if (get_termcaps(buf))
			continue ;
		else if ((!((!index && (char)buf == SEPARATOR_CHAR) || \
			(index && (char)buf == SEPARATOR_CHAR && \
			((char*)line->content)[index - 1] == SEPARATOR_CHAR))) && \
			(!(line = ft_arrayadd(line, (char[1]){(char)buf}, index++, 1))))
				errors(0, "malloc failed", env);
}
