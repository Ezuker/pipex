/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:36:19 by bcarolle          #+#    #+#             */
/*   Updated: 2023/12/13 15:25:44 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include "./ft_printf/ft_printf.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>

typedef enum e_bool
{
	false,
	true,
}			t_bool;

typedef struct s_data
{
	int		fd_infile;
	int		fd_outfile;
	t_bool	here_doc;
	t_bool	is_valid;
	char	***cmds;
	char	**envpath;
	char	**cmdspath;
	int		iteration;
}			t_data;

void	parsing_pipex(t_data *data, char **argv, int argc, char **envp);
char	*ft_addslash(char *s1, char *s2);
#endif
