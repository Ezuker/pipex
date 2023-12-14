/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:35:49 by bcarolle          #+#    #+#             */
/*   Updated: 2023/12/15 00:56:30 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_data(t_data *data, char **argv, int argc, char **envp)
{
	argv++;
	data->status_code = 0;
	if (!ft_strcmp(argv[0], "here_doc"))
	{
		data->here_doc = true;
		//parsing_here_doc(data, argv, argc, envp);
		data->iteration = 0;
	}
	else
	{
		data->here_doc = false;
		parsing_pipex(data, argv, argc, envp);
		data->iteration = 0;
	}
}

void	free_all(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->cmds && data->cmds[i] != NULL)
	{
		j = 0;
		while (data->cmds[i][j] != NULL)
			free(data->cmds[i][j++]);
		free(data->cmds[i++]);
	}
	free(data->cmds);
	i = 0;
	while (data->cmdspath && data->cmdspath[i] != NULL)
	{
		free(data->cmdspath[i++]);
	}
	free(data->cmdspath);
	i = 0;
	while (data->envpath && data->envpath[i])
		free(data->envpath[i++]);
	free(data->envpath);
	free(data);
}

void	child_process(t_data *data, int end[2], char **envp)
{
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(end[1]);
	if (access(data->cmdspath[data->iteration], X_OK) == -1)
		data->status_code = 127;
	if (execve(data->cmdspath[data->iteration], data->cmds[data->iteration], envp) == -1)
		data->status_code = 127;
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
	int		end[2];
	pid_t	fork_id;

	pipe(end);
	fork_id = fork();
	if (!fork_id)
	{
		dup2(data->fd_outfile, STDOUT_FILENO);
		close(data->fd_outfile);
		if (access(data->cmdspath[data->iteration], X_OK) == -1)
			data->status_code = 127;
		if (execve(data->cmdspath[data->iteration], data->cmds[data->iteration], envp) == -1)
			data->status_code = 127;
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

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		status_code;

	if (argc > 4)
	{
		data = ft_calloc(sizeof(t_data), 1);
		if (!data)
			exit (1);
		init_data(data, argv, argc, envp);
	}
	else
		exit (1);
	if (data->is_valid == false)
	{
		free_all(data);
		exit (1);
	}
	if (data->here_doc == false)
	{
		dup2(data->fd_infile, STDIN_FILENO);
		close(data->fd_infile);
		while (data->cmds[data->iteration + 1] != NULL)
		{
			exec_pipex(data, envp);
			data->iteration++;
		}
		final_exec(data, envp);
	}
	status_code = data->status_code;
	free_all(data);
	return (status_code);
}
