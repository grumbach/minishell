/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 14:32:59 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/25 19:55:25 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long		errors(const int erno, const char *comment)
{
	ft_printf("minishell: ");
	if (comment)
		ft_putendl(comment);
	if (erno == 0)
		ft_printf("System call returned -1\n");
	if (erno == 1)
		ft_printf("The Blood Moon is rising...\n");
	exit(EXIT_FAILURE);
}

void		minishell_ex(const char *path, char *const *av, char *const *envp)
{
	pid_t	pid;

	if ((pid = fork()) == -1)
		errors(0, "fork error");
	if (!pid)
	{
		if (execve(path, av, envp) == -1)
			errors(0, "execve error");
		ft_printf("bye\n");//?????why not seeing this????
		exit(EXIT_SUCCESS);
	}
	else if (wait(NULL) == -1)
		errors(0, "wait error");
}

static void	showoff(void)
{
	ft_printf("%s%s%s", BLUE, "           _       _     _          _ _\n"
	" _ __ ___ (_)_ __ (_)___| |__   ___| | |\n"
	"  | '_ ` _ \\| | '_ \\| / __| '_ \\ / _ \\ | |\n"
	"| | | | | | | | | | \\__ \\ | | |  __/ | |\n"
	"|_| |_| |_|_|_| |_|_|___/_| |_|\\___|_|_|\n\n$>", NORMAL);
}

int			main(int ac, char **av, char **envp)
{
	char 	*line;

	(void)av;
	showoff();
	while ((ac = ft_get_next_line(0, &line)))
	{
		if (ac == -1)
			errors(1, "failed to read");
		minishell_ex(line, NULL, envp);
		ft_memdel((void**)&line);
		ft_printf("$> ");
	}
	return (EXIT_SUCCESS);
}

// echo [-n(no\n)] [string ...]
// cd [-(goback)] [dir]
// setenv PATH="/bin:/usr/bin:/usr/sbin:usr/ucb/bin"
// unsetenv PATH
// envp
// exit
