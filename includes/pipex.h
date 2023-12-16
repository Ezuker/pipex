/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:36:19 by bcarolle          #+#    #+#             */
/*   Updated: 2023/12/15 23:33:47 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include "../ft_printf/ft_printf.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef enum e_bool
{
	false,
	true,
}			t_bool;

typedef struct s_pipex
{
	int	end0;
	int	end1;
}			t_pipex;

typedef struct s_data
{
	int		fd_infile;
	int		fd_outfile;
	t_bool	here_doc;
	t_bool	is_valid;
	char	***cmds;
	char	**envpath;
	char	**cpath;
	int		iter;
	int		status_code;
	t_pipex	pipex;
	char	*limiter;
}			t_data;

char	*get_next_line(int fd, char *limiter);
void	parsing_pipex(t_data *data, char **argv, int argc, char **envp);
void	parsing_heredoc(t_data *data, char **argv, int argc, char **envp);
char	*addslash(char *s1, char *s2);
int		init_cmds(t_data *data, char **argv, int argc);
void	init_path(t_data *data, char **envp);
void	check_cmds(t_data *data);
void	exec_pipex(t_data *data, char **envp);
void	final_exec(t_data *data, char **envp);
void	free_all(t_data *data);
#endif
