/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 14:32:59 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/28 08:21:02 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long		errors(const int erno, const char *comment)
{
	ft_putstr_fd("minishell: ", 2);
	if (comment)
		ft_putendl_fd(comment, 2);
	if (erno == 0)
		ft_putstr_fd("System Failure\n", 2);
	if (erno == 1)
		ft_putstr_fd("The Blood Moon is rising...\n", 2);
	exit(EXIT_FAILURE);
}

long		shell_error(const int erno, const char *comment)
{
	ft_putstr_fd("minishell: ", 2);
	if (comment)
		ft_putstr_fd(comment, 2);
	if (erno == 2)
		ft_putstr_fd(" : failed to change dir\n", 2);
	if (erno == 3)
		ft_putstr_fd(" : command not found\n", 2);
	if (erno == 4)
		ft_putstr_fd("A computer is like air conditioning,\n"
		"      It becomes useless when you open Windows.\n"
		"                                 Linus Torvalds\n", 2);
	return (0);
}

static void	showoff(void)
{
	ft_printf("%s%s%s$> ", BLUE, "           _       _     _          _ _\n"
	" _ __ ___ (_)_ __ (_)___| |__   ___| | |\n"
	"| '_ ` _ \\| | '_ \\| / __| '_ \\ / _ \\ | |\n"
	"| | | | | | | | | | \\__ \\ | | |  __/ | |\n"
	"|_| |_| |_|_|_| |_|_|___/_| |_|\\___|_|_|\n\n", NORMAL);
}

/*
** commands sorted in ascii order
*/

static void	set_commands(t_cmd *cmd)
{
	cmd[0] = (t_cmd){"cd", &mini_cd};
	cmd[1] = (t_cmd){"echo", &mini_echo};
	cmd[2] = (t_cmd){"env", &mini_env};
	cmd[3] = (t_cmd){"pwd", &mini_pwd};
	cmd[4] = (t_cmd){"setenv", &mini_setenv};
	cmd[5] = (t_cmd){"unsetenv", &mini_unsetenv};
}

int			main(int ac, char **av, char **envp)
{
	t_cmd	cmd[BUILT_IN_CMD_NB];
	t_array	*line;

	showoff();
	(void)av;
	(void)ac;
	if (!(line = ft_arraynew(sizeof(char))))
		errors(0, "malloc failed");
	ft_bzero(&cmd, sizeof(cmd));
	set_commands(cmd);
	mini_parse(line, cmd, envp);
	ft_arraydel(&line);
	return (EXIT_SUCCESS);
}
