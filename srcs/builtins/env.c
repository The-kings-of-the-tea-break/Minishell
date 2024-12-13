/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:15:36 by saberton          #+#    #+#             */
/*   Updated: 2024/12/13 16:59:33 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(t_data *data, int fd)
{
	t_env	*tmp;

	tmp = data->cpy_env;
	while (tmp)
	{
		ft_putstr_fd(tmp->type, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(tmp->value, fd);
		ft_putstr_fd("\n", fd);
		tmp = tmp->next;
	}
	ft_putstr_fd("PWD : je suis DANS LE BUILTINS\n", fd);
}

static void	check_only_env(t_data *data, t_token *tok, int fd)
{
	t_token	*tmp;
	int		err;

	err = 0;
	tmp = tok;
	if (tmp->next)
		err = 1;
	if (err == 0)
		print_env(data, fd);
	else
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
}

void	handle_env(t_data *data, t_token *tok, int fd_out)
{
	if (!tok->next)
		print_env(data, fd_out);
	else
		check_only_env(data, tok, fd_out);
}
