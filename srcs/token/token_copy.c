/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:06:50 by kepouliq          #+#    #+#             */
/*   Updated: 2024/11/25 17:24:09 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_operateur(char *line, int *i)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
		return (3);
	if (line[*i] == '<' && line[*i + 1] == '<')
		return (4);
	if (line[*i] == '<' && line[*i + 1] != '<')
		return (60);
	if (line[*i] == '>' && line[*i + 1] != '>')
		return (62);
	return (0);
}

char	*ft_copy_pipe(int *i)
{
	char	*dup;

	dup = malloc(sizeof(char) * 2);
	if (!dup)
		return (NULL);
	dup[0] = '|';
	dup[1] = '\0';
	(*i)++;
	return (dup);
}

char	*ft_copy_operateur(int *i, int j)
{
	char	*dup;

	dup = malloc(sizeof(char) * 3);
	if (!dup)
		return (NULL);
	if (j == 3)
	{
		dup[0] = '>';
		dup[1] = '>';
		dup[2] = '\0';
		(*i) += 2;
	}
	else if (j == 4)
	{
		dup[0] = '<';
		dup[1] = '<';
		dup[2] = '\0';
		(*i) += 2;
	}
	else if (j == 60)
	{
		dup[0] = '<';
		dup[1] = '\0';
		dup[2] = '\0';
		(*i)++;
	}
	else if (j == 62)
	{
		dup[0] = '>';
		dup[1] = '\0';
		dup[2] = '\0';
		(*i)++;
	}
	return (dup);
}