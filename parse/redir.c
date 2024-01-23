/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:42:39 by gykoh             #+#    #+#             */
/*   Updated: 2024/01/23 13:42:40 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*new_redir(t_type type, char *filename)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = type;
	new->filename = filename;
	new->next = NULL;
	return (new);
}

void	add_back_redir(t_redir **redir, t_redir *new)
{
	t_redir	*curr;

	if (!redir || !new)
		return ;
	if (!*redir)
	{
		*redir = new;
		return ;
	}
	curr = *redir;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}

void	free_redir(t_redir *redir)
{
	t_redir	*curr;
	t_redir	*tmp;

	if (!redir)
		return ;
	curr = redir;
	while (curr)
	{
		tmp = curr->next;
		free(curr->filename);
		free(curr);
		curr = tmp;
	}
}
