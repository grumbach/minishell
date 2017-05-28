/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 14:32:59 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/28 04:54:26 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long		errors(const int erno, const char *comment)
{
	ft_putstr_fd("minishell: ", 2);
	if (comment)
		ft_putendl_fd(comment, 2);
	if (erno == 0)
		ft_putstr_fd("System call returned -1\n", 2);
	if (erno == 1)
		ft_putstr_fd("The Blood Moon is rising...\n", 2);
	exit(EXIT_FAILURE);
}

long		shell_error(const int erno, const char *comment)
{
	ft_putstr_fd("minishell: ", 2);
	if (comment)
		ft_putstr_fd(comment, 2);
	if (erno == 1)
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
	cmd[3] = (t_cmd){"setenv", &mini_setenv};
	cmd[4] = (t_cmd){"unsetenv", &mini_unsetenv};
	cmd[5] = (t_cmd){"unsetenv", &mini_unsetenv};//
	cmd[6] = (t_cmd){"unsetenv", &mini_unsetenv};//
	cmd[7] = (t_cmd){"unsetenv", &mini_unsetenv};//
	cmd[8] = (t_cmd){"unsetenv", &mini_unsetenv};//
	cmd[9] = (t_cmd){"unsetenv", &mini_unsetenv};//
	cmd[10] = (t_cmd){"unsetenv", &mini_unsetenv};//
}

int			main(int ac, char **av, char **envp)
{
	t_cmd	cmd[BUILT_IN_CMD_NB];
	char 	*line;

	ft_bzero(&cmd, sizeof(cmd));
	(void)av;
	showoff();
	set_commands(cmd);
	while ((ac = ft_get_next_line(0, &line)))
	{
		if (ac == -1 || !line)
			errors(1, "failed to read");
		if (!mini_parse(cmd, line, envp))
			break ;
		ft_memdel((void**)&line);
		ft_printf("$> ");
	}
	return (EXIT_SUCCESS);
}
