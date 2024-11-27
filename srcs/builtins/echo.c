/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:53:43 by kepouliq          #+#    #+#             */
/*   Updated: 2024/11/27 15:00:40 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_flag(const char *line)
{
	int	j;

	if (line[0] != '-' || line[1] != 'n')
		return (0);
	j = 1;
	while (line[j] == 'n')
		j++;
	if (line[j] == '\0')
		return (1);
	return (0);
}

static int	flag_detector(t_data *data)
{
	t_token	*tmp;
	int		i;

	i = 1;
	tmp = data->token->next;
	while (tmp && is_valid_flag(tmp->value))
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	handle_echo(t_data *data)
{
	int		flag;
	int		flag_start;
	t_token	*tmp;

	tmp = data->token;
	flag = flag_detector(data);
	flag_start = flag;
	while (flag)
	{
		tmp = tmp->next;
		flag--;
	}
	while (tmp)
	{
		ft_putstr_fd(tmp->value, 0);
		if (tmp->next)
			ft_putstr_fd(" ", 0);
		tmp = tmp->next;
	}
	if (flag_start == 1)
		ft_putstr_fd("\n", 0);
}
