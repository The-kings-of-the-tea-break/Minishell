/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:27:25 by saberton          #+#    #+#             */
/*   Updated: 2024/12/15 08:33:34 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define INVALID_VAL_EXPORT "minishell: export: `': not a valid identifier\n"
# define INVALID_DOUBLE_APPEND "minishell: syntax error near unexpected token \
`>>'\n"
# define INVALID_SIMPLE_APPEND "minishell: syntax error near unexpected token \
`>'\n"
# define INVALID_TRIPLE_HEREDOC "minishell: syntax error near unexpected token \
`<<<'\n"
# define INVALID_DOUBLE_HEREDOC "minishell: syntax error near unexpected token \
`<<'\n"
# define INVALID_SIMPLE_HEREDOC "minishell: syntax error near unexpected token \
`<'\n"
# define INVALID_ARG_ENV "minishell: env: too many arguments\n"
# define INVALID_ARG_CD "minishell: cd: too many arguments\n"

#endif