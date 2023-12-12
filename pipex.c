/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:35:49 by bcarolle          #+#    #+#             */
/*   Updated: 2023/12/12 23:28:42 by bcarolle         ###   ########.fr       */
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
	// int	i;

	// i = -1;
	// while (data->cmds[i++] != NULL)
	// 	free(data->cmds[i]);
	// i = -1;
	// while (data->path[i++] != NULL)
	// 	free(data->path[i]);
	close(data->fd_infile);
	close(data->fd_outfile);
	free(data);
}

void	child_process(t_data *data, int end[2])
{
	char	**envp;

	envp = NULL;
	dup2(data->fd_infile, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(data->fd_infile);
	sleep(3); //test
	execve(data->cmdspath[data->iteration], data->cmds[data->iteration], envp);
}

void	parent_process(t_data *data, int end[2])
{
	char	**envp;

	envp = NULL;
	wait(NULL);
	dup2(data->fd_outfile, STDOUT_FILENO);
	dup2(end[0], STDIN_FILENO);
	close(end[1]);
	close(data->fd_outfile);
	execve(data->cmdspath[data->iteration + 1], data->cmds[data->iteration + 1], envp);
}

void	exec_pipex(t_data *data)
{
	int		end[2];
	pid_t	fork_id;

	pipe(end);
	fork_id = fork();
	if (!fork_id)
	{
		printf("child\n");
		child_process(data, end);
	}
	else
	{
		printf("parent\n");
		parent_process(data, end);
	}
	data->iteration = data->iteration + 1;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (argc > 4)
		init_data(data, argv, argc, envp);
	else
	{
		free(data);
		return (1);
	}
	if (data->is_valid == false)
	{
		printf("Error\n");
		free_all(data);
		return (1);
	}
	// if (data->here_doc)
	// 	exec_here_doc();
	// else
	while (data->cmds[data->iteration] != NULL)
	{
		exec_pipex(data);
		printf("iteration\n");
	}
	return (0);
}
