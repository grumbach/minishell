/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 00:16:00 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/28 18:03:16 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		env_size(t_env *env)
{
	int			i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

static void		exec_cmd(const char *path, char *const *args, t_env *env)
{
	char	**envp;
	t_env	*tail;
	pid_t	pid;
	int		i;

	tail = env;
	i = 0;
	if (!(envp = ft_memalloc(env_size(env) * sizeof(char*))))
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

static char		**fill_argv(char *args)
{
	char		**argv;
	int			i;
	int			words;

	argv = NULL;
	words = 0;
	i = -1;
	while (args[++i])
		if ((i && args[i - 1] == SEPARATOR_CHAR) || \
			(!i && args[i] != SEPARATOR_CHAR))
			words++;
	if (!(argv = ft_memalloc(sizeof(char*) * (words + 1))))
		return (NULL);
	i = 0;
	while (*args && words--)
	{
		argv[i++] = args;
		while (*args && *args != SEPARATOR_CHAR)
			args++;
		if (*args == SEPARATOR_CHAR)
			*args++ = '\0';
	}
	return (argv);
}

static char		*fill_path(char *path, const char *command, t_env *env)
{
	char		*correctpath;
	int			i;

	if (!(correctpath = ft_strnew(ft_strlen(path) + ft_strlen(command) + 2)))
		errors(0, "malloc failed", &env);
	path += ft_strlen("PATH=");
	while (*path)
	{
		i = 0;
		while (*path && *path != ':')
			correctpath[i++] = *path++;
		correctpath[i] = '\0';
		ft_strcat(correctpath, "/");
		ft_strcat(correctpath, command);
		if (!access(correctpath, F_OK))
			return (correctpath);
		else if (*path)
			path++;
	}
	return (NULL);
}

int				mini_exec(char *command, char *args, t_env *env)
{
	char	*path;
	char	**argv;

	path = NULL;
	argv = NULL;
	if (!(path = mini_whereis_env("PATH=", env)))
		return (shell_error(5, "PATH"));
	if (args && *args && !(argv = fill_argv(args)))
		errors(0, "malloc failed", &env);
	if (*command && (path = fill_path(path, command, env)))
		exec_cmd(path, argv, env);
	free(argv);
	free(path);
	return (!!path);
}
