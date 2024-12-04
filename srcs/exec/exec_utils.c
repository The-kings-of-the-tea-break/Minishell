/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:54:46 by saberton          #+#    #+#             */
/*   Updated: 2024/12/04 17:59:59 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_in_line(t_data *data)
{
	t_token	*tmp;
	int		pipe;

	tmp = data->token;
	pipe = 0;
	if (!tmp)
		return (0);
	while (tmp)
	{
		if (tmp->type == PIPE)
			pipe++;
		tmp = tmp->next;
	}
	return (pipe);
}

t_enum	wich_type_exec(t_data *data)
{
	int		choice;
	t_token	*tmp;

	choice = 0;
	tmp = data->token;
	while (tmp)
	{
		if (tmp->type == INFILE)
			return (INFILE);
		else if (tmp->type == OUTFILE)
			return (OUTFILE);
		else if (tmp->type == APPEND)
			return (APPEND);
		else if (tmp->type == HEREDOC)
			return (HEREDOC);
		tmp = tmp->next;
	}
	return (CMD);
}

t_token	*recup_tok_after_pipe(t_token *tmp)
{
	while (tmp)
	{
		if (tmp->type == PIPE && tmp->next)
			return (tmp->next);
		tmp = tmp->next;
	}
	return (NULL);
}

static int	len_cmd(t_token *tok)
{
	t_token	*tmp;
	int		i;

	i = 1;
	tmp = tok->next;
	if (!tmp)
		return (i);
	while (tmp)
	{
		if (tmp->type != WORD)
			break ;
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**recup_cmd(t_data *data, t_token *tok)
{
	char	**cmd;
	t_token	*tmp;
	int		i;

	i = 1;
	(void)data;
	cmd = malloc(sizeof(char *) * (len_cmd(tok) + 1));
	cmd[0] = ft_strdup(tok->value);
	tmp = tok->next;
	if (!tmp || len_cmd(tok) == 1)
		return (cmd[i] = NULL, cmd);
	while (tmp)
	{
		if (tmp->type != WORD)
			break ;
		cmd[i] = ft_strdup(tmp->value);
		tmp = tmp->next;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}
