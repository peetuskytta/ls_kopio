/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:45:58 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/06 21:34:57 by pskytta          ###   ########.fr       */
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
	int				f_all;
	int				f_long;
	int				f_reve;
	int				f_recu;
	int				f_time;
	int				padding[2];
	int				file_count;
	int				flag_count;
	int				link_count;
	int				arg_count;
	char			**list;
	DIR				*dir;
	struct dirent	*ent;
	char			path[1024];
}	t_data;

typedef struct s_file
{
	char			name[255];
	struct stat		stats;
}	t_file;

int		file_count(t_data *info);
t_file	*read_dir_stream(t_data *info, const char *dirname, int i);
void	ls_recursive(t_data *info, const char *dirname, int i);
void	ch_error(char c);
void	command_not_found(char *str);
void	flag_check(t_data *info, char *str);
void	flag_save(char c, t_data *info);
void	init_variables(t_data *info);
void	ls_driver(t_data *info, char *dirname);
void	ls_only(t_data *info, int i);
void	parse_flags(char **str, t_data *info);
void	primary_checks(char **str, int args, t_data *info);
void	print_short(t_file *arr, t_data *info);
void	sort_driver(t_file *arr, t_data *info);
void	sort_list_ascending(char **list, int n);
void	sort_struct_array_asc(t_file *arr, int n);
void	sort_struct_reverse(t_file *arr, int end);
void	sort_struct_time(t_file *arr, int n);
void	usage_error();
void	useful(t_data *data);
void	swap_struct(t_file *first, t_file *second);
int		is_directory(struct stat file);
void	path_maker(char *start, char *name);
void	ls_with_flags(t_data *info);


#endif
