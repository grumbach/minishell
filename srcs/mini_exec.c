/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 00:16:00 by agrumbac          #+#    #+#             */
/*   Updated: 2017/06/01 15:32:06 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		exec_cmd(const char *path, char **args, t_env *env)
{
	char	**envp;
	t_env	*tail;
	pid_t	pid;
	int		i;

	tail = env;
	i = 0;
	if (!(envp = ft_memalloc((mini_env_size(env) + 1) * sizeof(char *))))
		errors(0, "malloc error", &env);
	while (tail)
	{
		envp[i++] = tail->content;
		tail = tail->next;
	}
	envp[i] = NULL;
	if ((pid = fork()) == -1)
		errors(0, "fork error", &env);
	if (!pid)
	{
		if (execve(path, args, envp) == -1)
			shell_error(3, path);
	}
	else
		waitpid(pid, NULL, 0);
	free(envp);
}

static char		**fill_argv(char *command, char *args)
{
	char		**argv;
	int			i;
	int			words;

	argv = NULL;
	words = 0;
	i = -1;
	while (args && args[++i])
		if ((i && args[i - 1] == SEPARATOR_CHAR) || \
			(!i && args[i] != SEPARATOR_CHAR))
			words++;
	if (!(argv = ft_memalloc(sizeof(char*) * (words + 2))))
		return (NULL);
	argv[0] = command;
	i = 1;
	while (args && *args && words--)
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

	if (!path)
		return (NULL);
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
		if (!access(correctpath, F_OK) && !access(correctpath, X_OK))
			return (correctpath);
		else if (*path)
			path++;
	}
	free(correctpath);
	return (NULL);
}

int				exec_or_error(char *command, char **argv, t_env *env)
{
	struct stat			stats;
	char				*lastslash;

	if ((lastslash = ft_strrchr(command, '/')) && *(lastslash + 1))
	{
		if (!access(command, F_OK))
		{
			if (!access(command, X_OK) && \
			lstat(command, &stats) != -1 && !(S_ISDIR(stats.st_mode)))
			{
				exec_cmd(command, argv, env);
				return (1);
			}
			else
				return (shell_error(2, command));
		}
		else
			return (shell_error(6, command));
	}
	else
		return (shell_error(3, command));
}

void			mini_exec(char *command, char *args, t_env *env)
{
	char	*path;
	char	**argv;

	path = NULL;
	argv = NULL;
	if (!(path = mini_whereis_env("PATH", env)))
		shell_error(5, "PATH");
	if (!(argv = fill_argv(command, args)))
		errors(0, "malloc failed", &env);
	if (*command)
	{
		if ((path = fill_path(path, command, env)))
			exec_cmd(path, argv, env);
		else
			exec_or_error(command, argv, env);
	}
	free(argv);
	free(path);
}
