/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:35:49 by bcarolle          #+#    #+#             */
/*   Updated: 2023/12/13 18:35:45 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_data(t_data *data, char **argv, int argc, char **envp)
{
	argv++;
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
	if (execve(data->cmdspath[data->iteration], data->cmds[data->iteration], envp) == -1)
		perror("Error");
}

void	parent_process(int end[2])
{
	wait(NULL);
	dup2(end[0], STDIN_FILENO);
	close(end[1]);
}

void	parent_process_final(t_data *data, int end[2], char **envp)
{
	wait(NULL);
	dup2(end[0], STDIN_FILENO);
	dup2(data->fd_outfile, STDOUT_FILENO);
	close(end[1]);
	close(data->fd_outfile);
	if (execve(data->cmdspath[data->iteration], data->cmds[data->iteration], envp) == -1)
		perror("Error");
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
	data->iteration = data->iteration + 1;
}

void	exec_final(t_data *data, char **envp)
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
		parent_process_final(data, end, envp);
	}
	data->iteration = data->iteration + 1;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc > 4)
	{
		data = ft_calloc(sizeof(t_data), 1);
		if (!data)
			return (1);
		init_data(data, argv, argc, envp);
	}
	else
		return (1);
	if (data->is_valid == false)
	{
		free_all(data);
		return (1);
	}
	if (data->here_doc == false)
	{
		dup2(data->fd_infile, STDIN_FILENO);
		while (data->cmds[data->iteration + 1] != NULL)
			exec_pipex(data, envp);
		exec_final(data, envp);
	}
	free_all(data);
	return (0);
}
