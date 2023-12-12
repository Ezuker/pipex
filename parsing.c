/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:40:44 by bcarolle          #+#    #+#             */
/*   Updated: 2023/12/12 19:23:06 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	open_files(t_data *data, char **argv, int argc)
{
	int	fd_infile;
	int	fd_outfile;

	fd_infile = open(argv[0], O_RDONLY, 0777);
	if (fd_infile == -1)
		return (0);
	fd_outfile = open(argv[argc - 2], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd_outfile == -1)
	{
		close(fd_infile);
		return (0);
	}
	data->fd_infile = fd_infile;
	data->fd_outfile = fd_outfile;
	return (1);
}

static int	init_cmds(t_data *data, char **argv, int argc)
{
	int		i;
	char	**cmdspath;

	data->cmds = malloc(sizeof(char **) * (argc - 2));
	cmdspath = malloc(sizeof(char *) * (argc - 2));
	if (!data->cmds)
		return (0);
	i = 1;
	while (i < argc - 2)
	{
		data->cmds[i - 1] = ft_split(argv[i], ' ');
		if (!data->cmds[i - 1])
			return (0);
		i++;
	}
	data->cmds[i - 1] = NULL;
	data->cmdspath = cmdspath;
	return (1);
}

void	init_path(t_data *data, char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[++i] != NULL)
	{
		path = ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i]));
		if (path)
			break ;
		i++;
	}
	data->envpath = ft_split(path + 5, ':');
}

static int	check_cmds(t_data *data, char **envp)
{
	int		i;
	int		j;
	char	*path;

	init_path(data, envp);
	i = -1;
	while (data->cmds[++i] != NULL)
	{
		j = -1;
		while (data->envpath[++j] != NULL)
		{
			path = ft_addslash(data->envpath[j]);
			path = ft_strjoin(path, data->cmds[i][0]);
			if (access(path, F_OK) != -1)
				break ;
		}
		data->cmdspath[i] = path;
		if (access(path, F_OK) == -1)
			return (0);
	}
	return (1);
}

void	parsing_pipex(t_data *data, char **argv, int argc, char **envp)
{
	if (!open_files(data, argv, argc))
	{
		data->is_valid = false;
		return ;
	}
	if (!init_cmds(data, argv, argc))
	{
		data->is_valid = false;
		return ;
	}
	if (!check_cmds(data, envp))
	{
		data->is_valid = false;
		return ;
	}
	data->is_valid = true;
}
