/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:39:24 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/20 20:44:38 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_go_home(t_data *data)
{
	char	*home_path;

	home_path = get_home_env(data);
	if (!home_path)
	{
		data->err = 1;
		data->exit_status = 1;
		return ;
	}
	change_old_env_pwd(data, get_actual_env_path(data));
	chdir(home_path);
	change_env_pwd(data);
}

static void	handle_cd_dash(t_data *data, int fd_out)
{
	char	*new_path;
	t_env	*tmp;

	tmp = data->cpy_env;
	new_path = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, "OLDPWD") == 0)
		{
			new_path = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	change_old_env_pwd(data, get_actual_env_path(data));
	chdir(new_path);
	change_env_pwd(data);
	write_str_fd(data, "cd", new_path, fd_out);
	write_str_fd(data, "cd", "\n", fd_out);
	free(new_path);
}

void	change_directory(t_data *data, t_token *tok, int fd_out)
{
	if (access(tok->next->value, F_OK) == -1
		&& ft_strcmp(tok->next->value, "-"))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(data->token->next->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->exit_status += 1;
		return ;
	}
	else if (!ft_strcmp(tok->next->value, "-"))
		handle_cd_dash(data, fd_out);
	else
		change_old_env_pwd(data, get_actual_env_path(data));
	if (data->err)
		return ;
	chdir(tok->next->value);
	change_env_pwd(data);
}

void	handle_cd(t_data *data, t_token *tok, int fd_out)
{
	if (!tok->next)
		return (cd_go_home(data));
	else if (tok->next)
	{
		if (tok->next->type != WORD || ft_strcmp(tok->next->value, "~") == 0)
			return (cd_go_home(data));
		else if (!ft_strcmp(tok->next->value, "--"))
			return ;
		if (tok->next->next)
		{
			if (tok->next->type == WORD && tok->next->next->type == WORD)
				return (data->exit_status = 1, ft_putstr_fd(INVALID_ARG_CD, 2));
		}
		else
			return (change_directory(data, tok, fd_out));
	}
}
