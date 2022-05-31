/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:45:58 by pskytta           #+#    #+#             */
/*   Updated: 2022/05/31 20:42:43 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <unistd.h>
# include <dirent.h>
# include <stdio.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>

typedef struct s_data
{
	int			f_all;
	int			f_long;
	int			f_reve;
	int			f_recu;
	int			f_time;
	int			padding[2];
	int			file_count;
	int			flag_count;
	int			hd_count;
	int			arg_count;
}	t_data;

typedef struct s_file
{
	char			path[8192];
	struct dirent	*ent;
	struct stat		info;
	DIR				*dir;
}	t_file;


void	handle_flags(t_data *arr, char **str);
void	primary_checks(int args, char **str);
void	parse_flags(t_data *arr, char **str, int i);
void	init_flags(t_data *arr, char *str);
void	ch_error(char c);
void	flag_save(char c, t_data *arr);
void	print_double(char **str);
void	ls_driver(t_data *arr);

int	dot_count(const char *dir);
int		count_entries(const char *dirname, int count);

t_data	*dir_stream(const char *dirname, t_data *arr, int i);
t_data	store_data(struct dirent *ent, t_data f);
t_data	*dir_stream_all(const char *dirname, t_data *arr, int i);


#endif
