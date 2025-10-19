/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:15:12 by dogs              #+#    #+#             */
/*   Updated: 2025/10/19 10:59:43 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *ft_expand_var(const char *var, t_shenv *env, t_cli *cli)
{
    if (!var || !*var)
        return ft_strdup("");

    if (ft_strcmp(var, "?") == 0)
        return ft_itoa(cli ? cli->last_status : 0);
    if (!env)
        return ft_strdup("");
    for (t_shenv *cur = env; cur; cur = cur->next)
    {
        if (!cur->var)
            continue;
        char *eq = ft_strchr(cur->var, '=');
        if (!eq)
            continue;
        size_t name_len = eq - cur->var;
        size_t var_len = ft_strlen(var);
        if (name_len == var_len && ft_strncmp(cur->var, var, var_len) == 0) {
            return ft_strdup(eq + 1);
        }
    }

    return ft_strdup("");
}
char	*ft_expand_line(char *line, t_cli *cli)
{
    
	size_t		i;
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
			continue;
		}
		if (i < ft_strlen(line) && line[i] == '<' && line[i + 1] == '<')
		{
			if (ft_heredoc_len(line + i) <= 0)
				return (free(line), line = NULL, NULL);
			i += (ft_heredoc_len(line + i) - 1);
			continue;
		}
		i++;
	}
	t = ft_strtrim(line, " ");
	return (free(line), t);
}