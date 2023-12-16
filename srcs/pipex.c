/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:35:49 by bcarolle          #+#    #+#             */
/*   Updated: 2023/12/16 14:37:19 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_data(t_data *data, char **argv, int argc, char **envp)
{
	argv++;
	data->status_code = 0;
	parsing_pipex(data, argv, argc, envp);
	data->iter = 0;
}

void	free_all(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	close(data->fd_outfile);
	while (data->cmds && data->cmds[i] != NULL)
	{
		j = 0;
		while (data->cmds[i][j] != NULL)
			free(data->cmds[i][j++]);
		free(data->cmds[i++]);
	}
	free(data->cmds);
	i = 0;
	while (data->cpath && data->cpath[i] != NULL)
		free(data->cpath[i++]);
	free(data->cpath);
	i = 0;
	while (data->envpath && data->envpath[i])
		free(data->envpath[i++]);
	free(data->envpath);
	free(data);
}

void	pipex(t_data *data, char **envp)
{
	dup2(data->fd_infile, STDIN_FILENO);
	close(data->fd_infile);
	while (data->cmds[data->iter + 1] != NULL)
	{
		exec_pipex(data, envp);
		data->iter++;
	}
	final_exec(data, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		status_code;

	if (!*envp)
		return (2);
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
	pipex(data, envp);
	status_code = data->status_code;
	free_all(data);
	return (status_code);
}
