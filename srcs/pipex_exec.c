/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 23:27:01 by bcarolle          #+#    #+#             */
/*   Updated: 2023/12/15 23:35:06 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(t_data *data, int end[2], char **envp)
{
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(end[1]);
	if (access(data->cpath[data->iter], X_OK) == -1)
		data->status_code = 127;
	execve(data->cpath[data->iter], data->cmds[data->iter], envp);
	free_all(data);
	exit(0);
}

void	parent_process(int end[2])
{
	close(end[1]);
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
}

void	final_exec(t_data *data, char **envp)
{
	pid_t	fork_id;

	fork_id = fork();
	if (!fork_id)
	{
		dup2(data->fd_outfile, STDOUT_FILENO);
		close(data->fd_outfile);
		if (access(data->cpath[data->iter], X_OK) == -1)
			data->status_code = 127;
		execve(data->cpath[data->iter], data->cmds[data->iter], envp);
		free_all(data);
		exit(0);
	}
}

void	exec_pipex(t_data *data, char **envp)
{
	int		end[2];
	pid_t	fork_id;

	pipe(end);
	fork_id = fork();
	if (!fork_id)
	{
		child_process(data, end, envp);
	}
	else
	{
		parent_process(end);
	}
}
