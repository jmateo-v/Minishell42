/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:15:12 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 22:54:28 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*ft_expand_special(const char *var, t_cli *cli)
{
	if (ft_strcmp(var, "?") == 0)
	{
		if (cli)
			return (ft_itoa(cli->last_status));
		return (ft_itoa(0));
	}
	return (NULL);
}

static char	*ft_find_env_value(const char *var, t_shenv *env)
{
	t_shenv	*cur;
	char	*eq;
	size_t	name_len;
	size_t	var_len;

	cur = env;
	while (cur)
	{
		if (cur->var)
		{
			eq = ft_strchr(cur->var, '=');
			if (eq)
			{
				name_len = eq - cur->var;
				var_len = ft_strlen(var);
				if (name_len == var_len
					&& ft_strncmp(cur->var, var, var_len) == 0)
					return (ft_strdup(eq + 1));
			}
		}
		cur = cur->next;
	}
	return (NULL);
}

char	*ft_expand_var(const char *var, t_shenv *env, t_cli *cli)
{
	char	*res;

	if (!var || !*var)
		return (ft_strdup(""));
	res = ft_expand_special(var, cli);
	if (res)
		return (res);
	if (!env)
		return (ft_strdup(""));
	res = ft_find_env_value(var, env);
	if (res)
		return (res);
	return (ft_strdup(""));
}

char	*ft_expand_line(char *line, t_cli *cli)
{
	size_t	i;
	char	*t;

	(void)cli;
	if (!line)
		return (NULL);
	i = 0;
	while (line && i < ft_strlen(line))
	{
		if (line[i] == '\'' && (i == 0 || line[i - 1] != '\\'))
		{
			i += (ft_quoted_len(line + i, '\'') + 1);
			continue ;
		}
		if (i < ft_strlen(line) && line[i] == '<' && line[i + 1] == '<')
		{
			if (ft_heredoc_len(line + i) <= 0)
				return (free(line), line = NULL, NULL);
			i += (ft_heredoc_len(line + i) - 1);
			continue ;
		}
		i++;
	}
	t = ft_strtrim(line, " ");
	return (free(line), t);
}

void	cleanup(char *a, char *b, char *c, char *d)
{
	free(a);
	free(b);
	free(c);
	free(d);
}
