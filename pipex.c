/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:35:49 by bcarolle          #+#    #+#             */
/*   Updated: 2023/12/11 23:18:18 by bcarolle         ###   ########.fr       */
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

	cmds = malloc(sizeof(char *) * argc);
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
	data->cmds = cmds;
	return (1);
}

int	check_cmds(t_data *data, char **envp)
{

}

void	init_data(t_data *data, char **argv, int argc, char **envp)
{
	(void)envp;
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
