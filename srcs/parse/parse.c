/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:05:45 by kepouliq          #+#    #+#             */
/*   Updated: 2024/12/04 18:47:10 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtins(t_data *data)
{
	if (data->token && data->token->value != NULL)
	{
		if (ft_strcmp(data->token->value, "exit") == 0)
			return (data->token->type = BUILD, 1);
		else if (ft_strcmp(data->token->value, "env") == 0)
			return (data->token->type = BUILD, 1);
		else if (ft_strcmp(data->token->value, "echo") == 0)
			return (data->token->type = BUILD, 1);
		else if (ft_strcmp(data->token->value, "pwd") == 0)
			return (data->token->type = BUILD, 1);
		else if (ft_strcmp(data->token->value, "unset") == 0)
			return (data->token->type = BUILD, 1);
		else if (ft_strcmp(data->token->value, "export") == 0)
			return (data->token->type = BUILD, 1);
	}
	return (0);
}

int	handle_builtins(t_data *data, t_token *tok)
{
	if (tok && tok->value != NULL && tok->type == BUILD)
	{
		if (ft_strcmp(tok->value, "exit") == 0)
			handle_exit(data, tok);
		else if (ft_strcmp(tok->value, "env") == 0)
			handle_env(data, tok);
		else if (ft_strcmp(tok->value, "echo") == 0)
			handle_echo(tok);
		else if (ft_strcmp(tok->value, "pwd") == 0)
			handle_pwd();
		else if (ft_strcmp(tok->value, "unset") == 0)
			handle_unset(data, tok);
		else if (ft_strcmp(tok->value, "export") == 0)
			handle_export(data, tok);
		return (1);
	}
	return (0);
}

// static void	print_token(t_data *data)
// {
// 	int		i;
// 	t_token	*tok;
// 	t_token	*tmp;

// 	tmp = NULL;
// 	tok = data->token;
// 	if (data->err_quote)
// 		return ;
// 	i = 0;
// 	while (tok)
// 	{
// 		printf(MAGENTA "============== TOKEN %d ======================\n" RESET,
// 			i);
// 		tmp = tok->next;
// 		if (tok->prev)
// 		{
// 			printf("PREV = ");
// 			printf(BLUE "%s\t" RESET, tok->prev->value);
// 		}
// 		else
// 			printf("\t\t");
// 		printf(RED "%s " RESET, tok->value);
// 		printf(YELLOW "= %s" RESET, ft_enum_to_char(tok->type));
// 		if (tok->next)
// 		{
// 			printf("\tNEXT = ");
// 			printf(GREEN "%s\n" RESET, tok->next->value);
// 		}
// 		else
// 			printf("\n");
// 		printf("\n");
// 		tok = tmp;
// 		i++;
// 	}
// }

void	parse(t_data *data)
{
	ft_change_word_to_cmd(data);
	if (!good_syntaxe(data))
		return ;
	ft_check_access_cmd(data);
	// print_token(data);
	wich_exec(data);
}
