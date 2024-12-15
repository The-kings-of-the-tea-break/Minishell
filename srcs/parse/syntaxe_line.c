/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:30:41 by saberton          #+#    #+#             */
/*   Updated: 2024/12/15 08:28:49 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_err_syntaxe(char err, int i)
{
	int	j;

	j = 0;
	ft_putstr_fd("minishell: operation `", 2);
	while (i > 0)
	{
		ft_putchar_fd(err, 2);
		j++;
		i--;
	}
	ft_putstr_fd("' not handle\n", 2);
}

static int	check_syntaxe_in_quote(char *line, int open_quote, int i,
		t_data *data)
{
	while (line[i])
	{
		if (!open_quote && (line[i] == '\'' || line[i] == '\"'))
		{
			data->wich_quote_err = line[i];
			open_quote = 1;
		}
		else if ((line[i] == '\"' || line[i] == '\'')
			&& line[i] == data->wich_quote_err)
		{
			open_quote = 0;
			data->wich_quote_err = '\0';
		}
		if ((line[i] == '\n' || line[i] == ';' || line[i] == '\\')
			&& !open_quote)
			return (print_err_syntaxe(line[i], 1), 1);
		if (((line[i] == '&' && line[i + 1] == '&')
				|| (line[i] == '|' && line[i + 1] == '|')) && !open_quote)
			return (print_err_syntaxe(line[i], 2), 2);
		i++;
	}
	if (open_quote)
		return (3);
	return (0);
}

void	syntaxe_line(char *line, t_data *data)
{
	int	i;

	if (!line)
		return ;
	data->wich_quote_err = '\0';
	i = check_syntaxe_in_quote(data->line, 0, 0, data);
	if (i)
	{
		data->exit_status = 2;
		data->err = 1;
		if (i == 3)
			open_quote_exit(data);
		return ;
	}
}
