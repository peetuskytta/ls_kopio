/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:45:58 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/10 14:45:35 by pskytta          ###   ########.fr       */
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
	int				padding[3];
	int				file_count;
	int				flag_count;
	int				link_count;
	int				arg_count;
	char			**list;
	char			path[1024];
	DIR				*dir;
	struct dirent	*ent;
}	t_data;

typedef struct s_file
{
	char			name[255];
	int				len;
	struct stat		stats;
}	t_file;

int		file_count(t_data *info, const char *name);
t_file	*read_dir_stream(t_data *info, const char *name, int i, int f_count);
void	ch_error(char c);
void	command_not_found(char *str);
void	flag_check(t_data *info, char *str);
void	flag_save(char c, t_data *info);
void	init_variables(t_data *info);
void	ls_driver(t_data *info);
void	ls_only(t_data *info, int f_count);
void	ls_recursive(t_data *info, const char *name, int i);
void	ls_with_flags(t_data *info, const char *path);
void	parse_flags(char **str, t_data *info);
void	primary_checks(char **str, int args, t_data *info);
void	print_block_total(t_file *arr, int f_count);
void	print_double(char **str);
void	print_driver(t_file *arr, t_data *info, int f_count);
void	print_file_size(struct stat *stats, int pad);
void	print_filename(struct stat *stats, char *name);
void	print_links(struct stat *stats, int pad);
void	print_mod_time(struct stat *stats);
void	print_rights(struct stat *stats);
void	print_short(t_file *arr, int f_count);
void	print_users(struct stat *stats);
void	recurse_path_maker(char *path, const char *name, char *file);
void	save_padding(t_file *arr, t_data *info, int i, int f_count);
void	set_file_type(int mode, char *str);
void	sort_driver(t_file *arr, t_data *info, int f_count);
void	sort_list_ascending(char **list, int n);
void	sort_struct_array_asc(t_file *arr, int n);
void	sort_struct_reverse(t_file *arr, int end);
void	sort_struct_time(t_file *arr, int n);
void	space_after_str(char *str);
void	store_arguments(char **string, t_data *info, int i);
void	usage_error(void);
void	useful(t_data *data);
void	write_long_output(t_file *arr, t_data *info, int f_count, int i);

#endif
