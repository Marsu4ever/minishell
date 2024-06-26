/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:07:36 by uahmed            #+#    #+#             */
/*   Updated: 2024/05/06 16:07:38 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_valid_input(t_vars *vars, t_shell *shell)
{
	if (vars->input_line && vars->input_line[0])
		add_history(vars->input_line);
	vars->exit_status = shell->status;
	if (vars->input_line[0] == '\0')
	{
		shell->status = GREEN;
		ft_free_prompt(shell, NO);
		return (NO);
	}
	if (ft_syntax_error(vars) == YES)
	{
		shell->status = 258;
		ft_free_prompt(shell, NO);
		return (NO);
	}
	return (YES);
}

int	ft_prompt(t_shell *shell)
{
	shell->pipes = NULL;
	shell->pids = NULL;
	shell->vars = NULL;
	if (ft_init_shell(shell) == FAILURE)
		return (FAILURE);
	ft_init_vars(shell->vars);
	ft_signals(PARENT, OFF);
	shell->vars->input_line = readline(MINISHELL VERSION DOLLAR);
	if (shell->vars->input_line == NULL)
	{
		deallocate_all_envps(shell);
		ft_free_prompt(shell, NO);
		close(STDIN_FILENO);
		printf("\x1B[A");
		readline(MINISHELL VERSION DOLLAR);
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (g_signal_status != 0)
	{
		shell->status = g_signal_status;
		g_signal_status = 0;
	}
	return (SUCCESS);
}
