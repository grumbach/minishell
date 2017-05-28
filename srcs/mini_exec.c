/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 00:16:00 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/28 16:23:22 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		exec_cmd(const char *path, char *const *args, t_env *env)
{
	char	**envp;
	t_env	*tail;
	pid_t	pid;
	int		i;

	tail = env;
	i = 0;
	if (!(envp = ft_memalloc(ft_lstsize((t_list *)env) * sizeof(char*))))
		errors(0, "malloc error", &env);
	while (tail)
	{
		envp[i++] = tail->content;
		tail = tail->next;
	}
	if ((pid = fork()) == -1)
		errors(0, "fork error", &env);
	if (!pid)
	{
		if (execve(path, args, envp) == -1)
			errors(0, "execve error", &env);
		exit(EXIT_SUCCESS);
	}
	else if (wait(NULL) == -1)
		errors(0, "wait error", &env);
	free(envp);
}

char			*mini_whereis_env(char *envvar, t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(envvar, env->content, ft_strlen(envvar)))
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

static char		**fill_argv(char *args)// -sdf -sdf toto wowo
{
	ft_printf("fill_argv:%s\n", args);
	return ((char**)1);
}

static char		*fill_path(char *path, const char *command)// /bin/:toto/ro:as
{
	ft_printf("fill_path:%s--%s\n", path, command);
	return ((char*)1);
}

int				mini_exec(char *command, char *args, t_env *env)
{
	char	*path;
	char	**argv;

	path = NULL;
	argv = NULL;
	if (!(path = mini_whereis_env("PATH=", env)))
		return (shell_error(5, "PATH"));
	if (!(path = fill_path(path, command)) || \
		!(argv = fill_argv(args)))
		errors(0, "malloc failed", &env);
	exec_cmd(path, argv, env);
	free(argv);
	free(path);
	return (1);
}
