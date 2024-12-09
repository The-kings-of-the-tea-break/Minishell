/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:09:38 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/09 18:23:16 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	only_numeric(char *code)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (code[i] == '-' || code[i] == '+')
		i++;
	if (code[0] == '-')
		n = 1;
	while (code[i])
	{
		if (!ft_isdigit(code[i]))
			return (2);
		i++;
	}
	return (0);
}

static void	exit_with_exit_code(t_data *data, t_token *tok)
{
	int	exit_code;

	exit_code = 0;
	if (!only_numeric(tok->next->value))
	{
		exit_code = ft_atoi(tok->next->value);
		ft_putstr_fd("exit\n", 2);
		exit_prog(data, exit_code);
	}
}

static void	exit_num_arg_required(t_data *data, t_token *tok)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(tok->next->value, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit_prog(data, 2);
}

static void	check_overflow(t_data *data, char *nb)
{
	int		i;
	char	*overflow;

	i = ft_strlen(nb);
	if (nb[0] == '-')
		i--;
	if (i <= 18)
		return ;
	if (nb[0] == '-')
		overflow = ft_substr(nb, 1, 18);
	else
		overflow = ft_substr(nb, 0, 18);
	if (ft_atol(overflow) >= 922337203685477580 && ((ft_atol(nb + 18) > 7
				&& nb[0] != '-') || (ft_atol(nb + 18) > 8 && nb[0] == '-')))
	{
		free(overflow);
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(nb, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_prog(data, 2);
	}
	free(overflow);
	return ;
}

void	handle_exit(t_data *data, t_token *tok, int fd_out)
{
	if (tok->next)
		check_overflow(data, tok->next->value);
	if (tok->next && tok->next->next)
	{
		if (!only_numeric(tok->next->value))
			return (ft_putstr_fd("minishell: exit: too many arguments\n", 2));
		return (exit_num_arg_required(data, tok));
	}
	if (tok->next)
	{
		exit_with_exit_code(data, tok);
	}
	if (!tok->next)
	{
		ft_putstr_fd("exit\n", fd_out);
		exit_prog(data, 0);
	}
}
