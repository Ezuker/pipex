/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:35:49 by bcarolle          #+#    #+#             */
/*   Updated: 2023/12/12 11:53:48 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_files(t_data *data, char **argv, int argc)
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

int	init_cmds(t_data *data, char **argv, int argc)
{
	int		i;
	char	**cmds;

	cmds = malloc(sizeof(char *) * (argc - 2));
	if (!cmds)
		return (0);
	i = 1;
	while (i < argc - 2)
	{
		cmds[i - 1] = ft_strdup(argv[i]);
		if (!cmds[i - 1])
			return (0);
		i++;
	}
	cmds[i - 1] = NULL;
	data->cmds = cmds;
	return (1);
}

char	*ft_addslash(char *s1)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(sizeof(char) * (ft_strlen(s1) + 2));
	while (i < (int)(ft_strlen(s1)))
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '/';
	result[i + 1] = '\0';
	return (result);
}

char	*get_path(char **envp)
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
	return (path);
}

int	check_cmds(t_data *data, char **envp)
{
	int		i;
	char	*path;
	int		j;
	t_bool	save;

	path = get_path(envp);
	data->path = ft_split(path + 5, ':');
	i = 0;
	while (data->cmds[i] != NULL)
	{
		j = 0;
		save = false;
		while (data->path[++j] != NULL)
		{
			data->path[j] = ft_addslash(data->path[j]);
			path = ft_strjoin(data->path[j], ft_split(data->cmds[i], ' ')[0]);
			if (access(path, F_OK) != -1)
				save = true;
			free(path);
		}
		i++;
		if (!save)
			return (0);
	}
	return (1);
}

void	init_data(t_data *data, char **argv, int argc, char **envp)
{
	argv++;
	if (!ft_strcmp(argv[0], "here_doc"))
	{
		data->here_doc = true;
	}
	else
	{
		data->here_doc = false;
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
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (argc > 4)
		init_data(data, argv, argc, envp);
	else
		free(data);
	if (data->is_valid == false)
		printf("Error\n");
	return (0);
}
