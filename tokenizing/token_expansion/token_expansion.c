/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:11:57 by dogs              #+#    #+#             */
/*   Updated: 2025/11/04 22:01:52 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void cleanup(char *a, char *b, char *c, char *d)
{
    free(a);
    free(b);
    free(c);
    free(d);
}

t_token *ft_expand_tokens(t_token *tokens, int *len, t_cli *cli)
{
    if (!tokens || !len || *len <= 0 || !cli)
        return NULL;

    for (int i = 0; i < *len; i++) {
        char *result = ft_strdup("");
        if (!result)
            return NULL;

        if (!tokens[i].segments) {
            if (tokens[i].value)
                free(tokens[i].value);
            tokens[i].value = result;
            continue;
        }

        for (int s = 0; tokens[i].segments[s].value; s++) {
            t_segment *seg = &tokens[i].segments[s];
            char *expanded = NULL;
            char *seg_expanded = NULL;
            char *val = NULL;

            if (!seg->value) {
                expanded = ft_strdup("");
            } 
            else if (seg->type == QUOTE_SINGLE) 
            {
                expanded = ft_strdup(seg->value);
            }
            else if (seg->type == QUOTE_TRANSLATION)
            {
                expanded = ft_strdup(seg->value);
            }
            else if (seg->type == QUOTE_LITERAL)
            {
                expanded = ft_strdup(seg->value);
            }

             else
             {
                seg_expanded = ft_strdup("");
                
                if (!seg_expanded) 
                {
                    cleanup(result, expanded, seg_expanded, val);
                    return NULL;
                }
                for (int j = 0; seg->value[j]; j++)
                {
                    if (seg->value[j] == '$')
                    {
                        char next = seg->value[j + 1];

                        if (!next || !(ft_isalnum((unsigned char)next) || next == '_' || next == '?')) 
                        {
                            char *tmp2 = ft_strjoin(seg_expanded, "$");
                            free(seg_expanded);
                            seg_expanded = tmp2;

                            if (!seg_expanded) 
                            {
                                cleanup(result, expanded, seg_expanded, val);
                                return NULL;
                            }
                            continue;
                        }

                        j++;
                        char var[128] = {0};
                        int vi = 0;

                        if (seg->value[j] == '?') 
                        {
                            var[vi++] = '?';
                            j++;
                        } 
                        else 
                        {
                            while (seg->value[j] && (ft_isalnum((unsigned char)seg->value[j]) || seg->value[j] == '_')) 
                            {
                                if (vi < (int)sizeof(var) - 1)
                                    var[vi++] = seg->value[j++];
                                else
                                    j++;
                            }
                        }

                        j--;

                        val = ft_expand_var(var, *cli->env, cli);
                        if (!val)
                        val = ft_strdup("");

                        char *tmp2 = ft_strjoin(seg_expanded, val);
                        free(seg_expanded);
                        free(val);
                        seg_expanded = tmp2;

                        if (!seg_expanded) 
                        {
                            cleanup(result, expanded, seg_expanded, NULL);
                            return NULL;
                        }
                    } 
                    else 
                    {
                        char one[2] = { seg->value[j], '\0' };
                        char *tmp2 = ft_strjoin(seg_expanded, one);
                        free(seg_expanded);
                        seg_expanded = tmp2;

                        if (!seg_expanded)
                        {
                            cleanup(result, expanded, seg_expanded, val);
                            return NULL;
                        }
                    }
                }

                expanded = seg_expanded;
            }

            char *tmp = ft_strjoin(result, expanded);
            if (!tmp) {
                cleanup(result, expanded, seg_expanded, val);
                return NULL;
            }
            free(result);
            free(expanded);
            expanded = NULL;
            result = tmp;

            if (!result) {
                cleanup(result, expanded, seg_expanded, val);
                return NULL;
            }
        }

        if (tokens[i].value)
            free(tokens[i].value);

        tokens[i].value = result;
    }

    return tokens;
}