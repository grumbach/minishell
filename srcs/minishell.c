/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 14:32:59 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/28 18:18:40 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	showoff(int ac, char **av)
{
	(void)ac;
	(void)av;
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

void		mini_free_env(t_env **env, const char *who)
{
	t_env	*free_this;

	while (*env)
	{
		if (!who || !ft_strncmp(who, (*env)->content, ft_strlen(who)))
		{
			free_this = *env;
			*env = free_this->next;
			free(free_this->content);
			free(free_this);
		}
		else
			env = &(*env)->next;
	}
}

int			main(int ac, char **av, char **envp)
{
	t_cmd			cmd[BUILT_IN_CMD_NB];
	t_array			*line;
	t_env			*env;
	t_env			**tail;

	showoff(ac, av);
	env = NULL;
	tail = &env;
	while (envp && *envp)
	{
		if (!(*tail = ft_memalloc(sizeof(t_env))) || \
			(!((*tail)->content = ft_strdup(*envp))))
			errors(0, "malloc failed", &env);
		tail = &(*tail)->next;
		envp++;
	}
	if (!(line = ft_arraynew(sizeof(char))))
		errors(0, "malloc failed", &env);
	ft_bzero(&cmd, sizeof(cmd));
	set_commands(cmd);
	mini_parse(line, cmd, &env);
	ft_arraydel(&line);
	mini_free_env(&env, NULL);
	return (EXIT_SUCCESS);
}
