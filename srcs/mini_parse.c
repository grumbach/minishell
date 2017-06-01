/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 00:17:16 by agrumbac          #+#    #+#             */
/*   Updated: 2017/06/01 05:42:19 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_prompt(const t_array *line, const int index)
{
	char	buf[MAXPATHLEN + 1];

	if (!(getcwd(buf, MAXPATHLEN)))
		shell_error(5, "current working directory");
	ft_printf("%s[%s]%s$>%s ", BLUE, buf, GREEN, NORMAL);
	if (line)
		ft_printf("%.*s", index, line->content);//ret 0 if {\0}?? NB?
	return (0);
}

static int	puttc(const int tc)
{
	return (write(1, &tc, 1));
}

static int	get_termcaps(const int buf, t_array *line, int *index)
{
	if (ft_isprint(buf))
		return (!write(1, &buf, 1));
	if (buf == 12)
	{
		tputs(tgetstr("cl", 0), 1, &puttc);
		print_prompt(line, *index);
	}
	if (*index && buf == 127)
	{
		tputs(tgetstr("le", 0), 1, &puttc);
		tputs(tgetstr("dc", 0), 1, &puttc);
		(*index)--;
	}
	// ft_printf("[%d]\n", buf);// NUMBER NOTE
	return (1);
}

void		mini_parse(t_array *line, t_cmd *cmd, t_env **env)
{
	int		ret;
	int		index;
	int		buf;

	index = print_prompt(line, (buf = 0));
	while (buf != 4 && !(buf = 0) && \
		(ret = read(0, &buf, 4)))
		if (ret == -1)
			errors(1, "failed to read", env);
		else if ((char)buf == '\n' && write(1, &buf, 1))
		{
			if (!(line = ft_arrayadd(line, (char[1]){'\0'}, index, 1)))
				errors(0, "malloc failed", env);
			if (!mini_command(cmd, line->content, env))
				break ;
			index = print_prompt(NULL, 0);
			continue ;
		}
		else if (get_termcaps(buf, line, &index))
			continue ;
		else if ((!((!index && (char)buf == SEPARATOR_CHAR) || \
			(index && (char)buf == SEPARATOR_CHAR && \
			((char*)line->content)[index - 1] == SEPARATOR_CHAR))) && \
			(!(line = ft_arrayadd(line, (char[1]){(char)buf}, index++, 1))))
				errors(0, "malloc failed", env);
}
