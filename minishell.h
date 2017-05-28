/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 14:38:11 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/28 04:54:39 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include "ft_printf.h"

# define MAX_CMD_LEN 16

typedef struct	s_cmd
{
	char		name[MAX_CMD_LEN];
	int			(*cmd)(char *args, char **envp);
}				t_cmd;

/*
** minishell
*/

# define SEPARATOR_CHAR ' '

int			mini_parse(t_cmd *cmd, char *line, char **envp);
void		mini_exec(const char *path, char *const *args, char *const *envp);

/*
** errors
*/

long		errors(const int erno, const char *comment);
long		shell_error(const int erno, const char *comment);

/*
** built-in commands
*/

# define BUILT_IN_CMD_NB 11

int			mini_cd(char *args, char **envp);
int			mini_echo(char *args, char **envp);
int			mini_env(char *args, char **envp);
int			mini_setenv(char *args, char **envp);
int			mini_unsetenv(char *args, char **envp);

#endif
