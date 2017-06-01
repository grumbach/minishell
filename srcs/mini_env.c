/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 19:11:51 by agrumbac          #+#    #+#             */
/*   Updated: 2017/06/01 05:27:00 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (who)
				break ;
		}
		else
			env = &(*env)->next;
	}
}

int			mini_set_env(char *var, char *content, t_env **env)
{
	char 	*who;
	t_env	*new;

	if ((who = mini_whereis_env(var, *env)))
		mini_free_env(env, who);
	if (!(new = ft_memalloc(sizeof(t_env))) ||
		!(new->content = ft_strnjoin(3, var, "=", content)))
		return (errors(0, "malloc failed", env));
	while (*env)
		env = &(*env)->next;
	*env = new;
	return (1);
}

char		*mini_whereis_env(char *envvar, t_env *env)
{
	size_t		len;

	len = ft_strlen(envvar);
	while (env)
	{
		if (!ft_strncmp(envvar, env->content, len) && \
			env->content[len] == '=')
			return (env->content);
		env = env->next;
	}
	return (NULL);
}
