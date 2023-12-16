/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:40:18 by bcarolle          #+#    #+#             */
/*   Updated: 2023/12/16 15:00:18 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

static int	open_heredoc(t_data *data, char **argv, int argc)
{
	int	fd_outfile;

	fd_outfile = open(argv[argc - 2], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd_outfile == -1)
	{
		perror("Error");
		free(data);
		exit(2);
	}
	data->fd_outfile = fd_outfile;
	return (1);
}

int	init_cmds_heredoc(t_data *data, char **argv, int argc)
{
	int		i;

	data->cmds = ft_calloc(sizeof(char **), argc - 1);
	if (!data->cmds)
		return (0);
	data->cpath = ft_calloc(sizeof(char *), argc - 1);
	if (!data->cpath)
		return (0);
	i = 0;
	while (i < argc - 1)
		data->cpath[i++] = NULL;
	i = 1;
	while (i < argc - 1)
	{
		data->cmds[i - 1] = ft_split(argv[i - 1], ' ');
		if (!data->cmds[i - 1])
			return (0);
		i++;
	}
	data->cmds[i - 1] = NULL;
	return (1);
}

void	init_path_heredoc(t_data *data, char **envp)
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

void	check_cmds_heredoc(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (data->cmds[++i] != NULL)
	{
		j = -1;
		while (data->envpath[++j] != NULL)
		{
			data->cpath[i] = addslash(data->envpath[j], data->cpath[i]);
			data->cpath[i] = ft_strjoin(data->cpath[i], data->cmds[i][0]);
			if (access(data->cpath[i], F_OK) != -1)
				break ;
			if (access(data->cmds[i][0], F_OK) != -1)
			{
				data->cpath[i] = ft_strcpy(data->cpath[i], data->cmds[i][0]);
				break ;
			}
		}
		if (access(data->cpath[i], F_OK) == -1)
		{
			ft_printf("zsh: Command not found\n");
			data->status_code = 127;
		}
	}
}

void	parsing_heredoc(t_data *data, char **argv, int argc, char **envp)
{
	data->limiter = ft_strdup(argv[1]);
	open_heredoc(data, argv, argc);
	argv++;
	argv++;
	argc -= 2;
	if (!init_cmds_heredoc(data, argv, argc))
	{
		data->is_valid = false;
		return ;
	}
	init_path_heredoc(data, envp);
	check_cmds_heredoc(data);
	data->is_valid = true;
}
