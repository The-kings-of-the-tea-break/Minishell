/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:09:38 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/17 15:39:19 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	only_numeric(char *code)
// {
// 	int	i;

// 	i = 0;
// 	if (code[i] == '-' || code[i] == '+')
// 		i++;
// 	while (code[i])
// 	{
// 		if (!ft_isdigit(code[i]))
// 			return (2);
// 		i++;
// 	}
// 	return (0);
// }

// static void	exit_with_exit_code(t_data *data, t_token *tok)
// {
// 	int	exit_code;

// 	exit_code = 0;
// 	if (!only_numeric(tok->next->value))
// 	{
// 		exit_code = ft_atoi(tok->next->value);
// 		ft_putstr_fd("exit\n", 2);
// 		exit_prog(data, exit_code);
// 	}
// }

// static void	exit_num_arg_required(t_data *data, t_token *tok)
// {
// 	ft_putstr_fd("exit\nminishell: exit: ", 2);
// 	ft_putstr_fd(tok->next->value, 2);
// 	ft_putstr_fd(": numeric argument required\n", 2);
// 	exit_prog(data, 2);
// }

// static int	check_overflow(char *nb)
// {
// 	int					i;
// 	int					sign;
// 	unsigned long long	result;
// 	unsigned long long	limit;

// 	i = 0;
// 	sign = 1;
// 	result = 0;
// 	limit = (unsigned long long)LLONG_MAX + 1;
// 	while (nb[i] == ' ' || (nb[i] >= 9 && nb[i] <= 13))
// 		i++;
// 	if (nb[i] == '+' || nb[i] == '-')
// 		if (nb[i++] == '-')
// 			sign = -1;
// 	while (nb[i] >= '0' && nb[i] <= '9')
// 	{
// 		result = result * 10 + (nb[i++] - '0');
// 		if ((sign == 1 && result > (unsigned long long)LLONG_MAX) || (sign == -1
// 				&& result > limit))
// 			return (1);
// 	}
// 	return (0);
// }

// void	handle_exit(t_data *data, t_token *tok, int fd_out)
// {
// 	if (tok->next)
// 	{
// 		if (check_overflow(tok->next->value))
// 		{
// 			ft_putstr_fd("exit\nminishell: exit: ", 2);
// 			ft_putstr_fd(tok->next->value, 2);
// 			ft_putstr_fd(": numeric argument required\n", 2);
// 			exit_prog(data, 2);
// 		}
// 	}
// 	if (tok->next && tok->next->next)
// 	{
// 		if (!only_numeric(tok->next->value))
// 			return (data->exit_status = 1,
// 				ft_putstr_fd("minishell: exit: too many arguments\n", 2));
// 		return (exit_num_arg_required(data, tok));
// 	}
// 	if (tok->next)
// 		exit_with_exit_code(data, tok);
// 	if (!tok->next)
// 	{
// 		ft_putstr_fd("exit\n", fd_out);
// 		exit_prog(data, 0);
// 	}
// }

/***** UGO ******/

static int	is_valid_longlong(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;
	unsigned long long	limit;

	i = 0;
	sign = 1;
	result = 0;
	limit = (unsigned long long)LLONG_MAX + 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if ((sign == 1 && result > (unsigned long long)LLONG_MAX)
			|| (sign == -1 && result > limit))
			return (EXIT_FAILURE);
	}
	if (str[i] != '\0')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	exit_numeric_error(t_token *tok, t_data *data)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(tok->next->value, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	exit_prog(data, ft_atoi("2"));
}

static int	handle_too_many_args(t_data *data)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	return (data->exit_status = 1);
}

void	handle_exit(t_data *data, t_token *tok, int fd_out)
{
	if (!tok->next)
	{
		ft_putstr_fd("exit\n", fd_out);
		exit_prog(data, EXIT_SUCCESS);
	}
	if (tok->next && is_valid_longlong(tok->next->value)
		&& !tok->next->next)
		exit_numeric_error(tok, data);
	if (tok->next && tok->next->next
		&& !is_valid_longlong(tok->next->value)
		&& !is_valid_longlong(tok->next->next->value))
		handle_too_many_args(data);
	if (tok->next && tok->next->next)
		exit_numeric_error(tok, data);
	ft_putstr_fd("exit\n", fd_out);
	exit_prog(data, ft_atoi(tok->next->value));
}
