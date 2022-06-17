/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:18:55 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/17 18:38:37 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <unistd.h>
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>

# define PATH_MAX 4096
# define MAX_NAME_LEN 255
# define TRUE 1
# define FALSE 0

typedef struct s_data
{
	int				f_all;
	int				f_long;
	int				f_reve;
	int				f_recu;
	int				f_time;
	int				nb_of_args;
	int				file_count;
	int				flag_count;
	int				link_count;
	int				arg_count;
	int				arguments_on;
	char			**list;
	//char			path[PATH_MAX];
	DIR				*dir;
	struct dirent	*ent;
}	t_data;

typedef struct s_file
{
	char			name[MAX_NAME_LEN];
	int				is_device;
	int				file_ok;
	int				len;
	struct stat		stats;
}	t_file;

int		file_count(t_data *info, const char *name);
int		return_major_or_minor(int rdev, int option);
t_file	*read_dir_stream(t_data *info, const char *name, int i, int f_count);
void	ch_error(char c);
void	command_not_found(char *str);
void	file_no_exist(char *str);
void	ls_driver(t_data *info, char *name);
void	ls_recursive(t_data *info, const char *name, int i);
void	ls_with_flags(t_data *info, const char *path);
void	no_directory_access(char *name);
void	no_flags(t_data *info, const char *path);
void	primary_checks(char **str, int args, t_data *info);
void	print_block_total(t_file *arr, int f_count);
void	print_dirname(char *dirname);
void	print_driver(t_file *arr, t_data *info, int f_count);
void	print_file_size(struct stat *stats);
void	print_filename(struct stat *stats, char *name);
void	print_from_string(char *str, int start, int n);
void	print_links(struct stat *stats);
void	print_major_and_minor(struct stat *stats);
void	print_mod_time(struct stat *stats);
void	print_rights(struct stat *stats, t_file *arr);
void	print_short(t_file *arr, int f_count);
void	print_users(struct stat *stats);
void	set_file_type(char *str, struct stat stats, t_file *arr);
void	sort_driver(t_file *arr, t_data *info, int f_count);
void	sort_list_ascending(char **list, int n);
void	sort_struct_array_asc(t_file *arr, int n);
void	sort_struct_reverse(t_file *arr, int end);
void	sort_struct_time(t_file *arr, int n);
void	space_after_nbr(int nbr);
void	space_after_str(char *str);
void	store_and_process_arguments(char **string, t_data *info);
void	usage_error(void);
void	write_args_long(t_file arr);
void	write_long_output(t_file *arr, int f_count, int i);

#endif
