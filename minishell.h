/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 14:38:11 by agrumbac          #+#    #+#             */
/*   Updated: 2017/06/01 15:15:20 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf.h"

# include <termios.h>
# include <sys/ioctl.h>
# include <sys/param.h>
# include <sys/stat.h>
# include <signal.h>
# include <term.h>

# define MAX_CMD_LEN 15
# define SEPARATOR_CHAR ' '

typedef struct		s_env
{
	char			*content;
	struct s_env	*next;
}					t_env;

typedef struct		s_cmd
{
	char			name[MAX_CMD_LEN + 1];
	int				(*cmd)(char *args, t_env **env);
}					t_cmd;

/*
** minishell
*/

void		mini_parse(t_array *line, t_cmd *cmd, t_env **env);
int			mini_command(t_cmd *cmd, char *line, t_env **env);
void		mini_exec(char *envvar, char *args, t_env *env);
int			mini_env_size(t_env *env);

/*
** env
*/

void		mini_free_env(t_env **env, const char *who);
int			mini_set_env(char *var, char *content, t_env **env);
char		*mini_whereis_env(char *command, t_env *env);

/*
** errors
*/

long		errors(const int erno, const char *comment, t_env **env);
long		shell_error(const int erno, const char *comment);
void		sig_handler(int sig);

/*
** built-in commands
*/

# define BUILT_IN_CMD_NB 6

int			mini_cd(char *args, t_env **env);
int			mini_echo(char *args, t_env **env);
int			mini_env(char *args, t_env **env);
int			mini_pwd(char *args, t_env **env);
int			mini_setenv(char *args, t_env **env);
int			mini_unsetenv(char *args, t_env **env);

#endif
