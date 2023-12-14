/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:40:44 by bcarolle          #+#    #+#             */
/*   Updated: 2023/12/15 00:51:17 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	open_files(t_data *data, char **argv, int argc)
{
	int	fd_infile;
	int	fd_outfile;

	fd_infile = open(argv[0], O_RDONLY, 0777);
	fd_outfile = open(argv[argc - 2], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd_outfile == -1 || fd_infile == -1)
	{
		if (fd_outfile != -1)
			close(fd_outfile);
		perror("Error");
		free(data);
		exit(2);
	}
	data->fd_infile = fd_infile;
	data->fd_outfile = fd_outfile;
	return (1);
}

static int	init_cmds(t_data *data, char **argv, int argc)
{
	int		i;

	data->cmds = ft_calloc(sizeof(char **), argc - 2);
	if (!data->cmds)
		return (0);
	data->cmdspath = ft_calloc(sizeof(char *), argc - 2);
	if (!data->cmdspath)
		return (0);
	i = 0;
	while (i < argc - 2)
		data->cmdspath[i++] = NULL;
	i = 1;
	while (i < argc - 2)
	{
		data->cmds[i - 1] = ft_split(argv[i], ' ');
		if (!data->cmds[i - 1])
			return (0);
		i++;
	}
	data->cmds[i - 1] = NULL;
	return (1);
}

void	init_path(t_data *data, char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i] != NULL)
	{
		path = ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i]));
		if (path)
			break ;
		i++;
	}
	data->envpath = ft_split(path + 5, ':');
}

void	check_cmds(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (data->cmds[++i] != NULL)
	{
		j = -1;
		while (data->envpath[++j] != NULL)
		{
			data->cmdspath[i] = addslash(data->envpath[j], data->cmdspath[i]);
			data->cmdspath[i] = ft_strjoin(data->cmdspath[i], data->cmds[i][0]);
			if (access(data->cmdspath[i], F_OK) != -1)
				break ;
			if (access(data->cmds[i][0], F_OK) != -1)
			{
				data->cmdspath[i] = ft_strcpy(data->cmdspath[i], data->cmds[i][0]);
				break ;
			}
		}
		if (access(data->cmdspath[i], F_OK) == -1)
		{
			ft_printf("zsh: Command not found\n");
			data->status_code = 127;
		}
	}
}

void	parsing_pipex(t_data *data, char **argv, int argc, char **envp)
{
	open_files(data, argv, argc);
	if (!init_cmds(data, argv, argc))
	{
		data->is_valid = false;
		return ;
	}
	init_path(data, envp);
	check_cmds(data);
	data->is_valid = true;
}
