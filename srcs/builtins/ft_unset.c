/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:33:42 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/29 17:53:56 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	skip_node(t_variable *node, char *arg, int is_env)
{
	t_variable	*tmp;

	while (node->next)
	{
		if (ft_strcmp(arg, node->next->name) == 0)
		{
			tmp = node->next;
			node->next = node->next->next;
			if (!is_env)
			{
				free(tmp->name);
				free(tmp->value);
			}
			free(tmp);
			return ;
		}
		node = node->next;
	}
}

/*
	It takes one ore more arguments, UPPERCASE letters only, with OR without $
	If exists : skip next node, replace its address with next next's one
	(in both env and export lists)
*/
void	ft_unset(t_cmdli **cmdli)
{
	int			i;
	char		**args;
	t_variable	*env;
	t_variable	*export;

	g_errno = 0;
	args = (*cmdli)->cmd_args;
	if (!args || !args[0])
		return ;
	i = 1;
	while (args[i])
	{
		env = ft_get_env();
		export = ft_get_export();
		skip_node(env, args[i], 1);
		skip_node(export, args[i], 0);
		++i;
	}
}
