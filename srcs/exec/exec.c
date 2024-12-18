/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:34:54 by saberton          #+#    #+#             */
/*   Updated: 2024/12/18 19:07:35 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_last_cmd(t_data *data, char *cmd_path)
{
	t_env	*env;
	t_env	*export;

	env = data->cpy_env;
	export = data->cpy_env2;
	while (env)
	{
		if (!ft_strcmp(env->type, "_"))
		{
			free(env->value);
			env->value = ft_strdup(cmd_path);
			break ;
		}
		env = env->next;
	}
	while (export)
	{
		if (!ft_strcmp(export->type, "_"))
		{
			free(export->value);
			export->value = ft_strdup(cmd_path);
			break ;
		}
		export = export->next;
	}
}

void	exec_cmd(t_data *data, char **env, char **cmd, t_token *tok)
{
	char	*cmd_path;
	char	**new_env;

	(void)env;
	if (!cmd || !*cmd)
		return ;
	cmd_path = valid_cmd(data, tok->value);
	if (!cmd_path)
		return ;
	if (!*cmd_path)
	{
		free(cmd_path);
		cmd_path = ft_strdup(*cmd);
		if (!cmd_path)
			return (failed_mess(data, "malloc failed", 1));
	}
	update_last_cmd(data, cmd_path);
	new_env = env_to_tab(data->cpy_env);
	if (!new_env)
		return (data->err = 1, failed_mess(data, "malloc failed", 1));
	data->exit_status = execve(cmd_path, cmd, new_env);
	if (data->exit_status == -1)
		data->err = 1;
	free(cmd_path);
}

void	exec_choice(t_data *data, t_token *tok)
{
	char	**cmd;

	cmd = recup_cmd(data, tok);
	// int i = 0;
	// while (cmd[i])
	// {
	// 	printf("cmd[%d] [%s]\n", i, cmd[i]);
	// 	i++;
	// }
	if (tok->type == BUILD)
		handle_builtins(data, tok, STDOUT_FILENO);
	else if (tok->type == CMD)
		exec_cmd(data, data->env, cmd, tok);
	ft_free_tab(cmd);
}

static void	simple_exec(t_data *data, t_token *tmp)
{
	pid_t	pid;

	if (data->err)
		return ;
	tmp = check_if_cmd_after_redir(data, tmp);
	if (tmp->type == BUILD)
	{
		exec_dup2_simple(data);
		handle_builtins(data, tmp, STDOUT_FILENO);
		if (dup2(data->pipe->orig_fds[0], STDIN_FILENO) == -1
			|| dup2(data->pipe->orig_fds[1], STDOUT_FILENO) == -1)
			return (failed_mess(data, "dup2 failed", 1));
	}
	else if (tmp->type == CMD)
	{
		pid = fork();
		if (pid == -1)
			return (failed_mess(data, "malloc failed", 1));
		if (pid == 0)
		{
			exec_dup2_simple(data);
			free_close_fds(data, 0);
			exec_choice(data, tmp);
		}
		else
			get_end_exec(data, 0, pid);
	}
}

static int	is_not_found(t_data *data)
{
	t_token	*tok;

	tok = data->token;
	while (tok)
	{
		if (tok->type == NOT_FOUND)
			return (1);
		tok = tok->next;
	}
	return (0);
}

void	wich_exec(t_data *data)
{
	t_token	*tmp;
	t_pipe	data_pipe;

	tmp = data->token;
	ft_bzero(&data_pipe, sizeof(t_pipe));
	data_pipe.data = data;
	data_pipe.fds = NULL;
	data_pipe.pid = NULL;
	data->pipe = &data_pipe;
	data_pipe.nb_pipe = pipe_in_line(data);
	data->pipe->orig_fds[0] = dup(STDIN_FILENO);
	data->pipe->orig_fds[1] = dup(STDOUT_FILENO);
	if (data->pipe->orig_fds[0] == -1 || data->pipe->orig_fds[1] == -1)
		return (failed_mess(data, "dup failed", 1));
	if (!is_not_found(data))
		data->exit_status = 0;
	if (data->pipe->nb_pipe > 0)
		ft_pipes(data);
	else
	{
		open_file(data, data->token);
		simple_exec(data, tmp);
		free_close_fds(data, 0);
	}
}
