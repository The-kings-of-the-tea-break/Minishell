/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 02:16:59 by saberton          #+#    #+#             */
/*   Updated: 2024/12/15 04:42:12 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_finish_expand(char *str, t_data *data, int count, int i)
{
	char	*var;

	var = extract_var(str + i, &i);
	if (is_exist_in_env(var, data))
		return (free(var), 1);
	free(var);
	if (count % 2 == 0)
		return (1);
	return (0);
}

int	dollar_in_str(char *str, t_data *data)
{
	int	i;
	int	open;
	int	count;

	i = 0;
	open = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		if (str[i] == '\'' && !open)
			open = 1;
		else if (str[i] == '\'' && open)
			open = 0;
		else if (str[i] == '$')
		{
			if (is_finish_expand(str, data, count, i))
				return (1);
		}
		i++;
	}
	return (0);
}

static char	*pair_impair_dollar(int dollar_count, char *result, char *pid_str,
		char *temp)
{
	while (dollar_count >= 2)
	{
		if (!result)
			result = ft_strdup(pid_str);
		else
		{
			temp = ft_strjoin(result, pid_str);
			free(result);
			result = temp;
		}
		dollar_count -= 2;
	}
	if (dollar_count == 1)
	{
		if (!result)
			result = ft_strdup("$");
		else
		{
			temp = ft_strjoin(result, "$");
			free(result);
			result = temp;
		}
	}
	return (result);
}

char	*expand_dollar_sequence(char **str, int *i)
{
	size_t	dollar_count;
	char	*pid_str;
	char	*result;
	char	*temp;

	temp = NULL;
	dollar_count = 0;
	pid_str = "(pid)";
	result = NULL;
	while ((*str)[*i] == '$')
	{
		dollar_count++;
		(*i)++;
	}
	result = pair_impair_dollar(dollar_count, result, pid_str, temp);
	return (result);
}
