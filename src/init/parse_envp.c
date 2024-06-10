/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkorpela <mkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:46:31 by mkorpela          #+#    #+#             */
/*   Updated: 2024/05/22 15:46:33 by mkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_array_length(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		i++;
	}
	return (i);
}

char	**malloc_envp(t_shell *shell, char **envp)
{
	char	**new_envp;
	int		i;
	int		num_of_envs;

	num_of_envs = ft_array_length(envp);
	new_envp = malloc(sizeof(char *) * (num_of_envs + 1));
	if (!new_envp)
	{
		exit (EXIT_FAILURE);
	}
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (new_envp[i] == NULL)
		{
			free_failed_2d_array(shell, envp, i);
			exit (EXIT_FAILURE);
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
