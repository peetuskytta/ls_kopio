/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:56:25 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/16 17:05:19 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	write_args_long(t_file arr, t_data *info)
{
	if (info->arg_count < 2)
		print_dirname(arr.name);
	print_rights(&arr.stats);
	print_links(&arr.stats, info->padding[0]);
	print_users(&arr.stats);
	print_file_size(&arr.stats, info->padding[1]);
	print_mod_time(&arr.stats);
	print_filename(&arr.stats, arr.name);
	ft_putchar('\n');
}

void	file_no_exist(char *str)
{
	ft_putstr("ls: ");
	ft_putstr(str);
	ft_putstr(": ");
	ft_putendl("No such file or directory");
}

void	no_directory_access(char *name)
{
	ft_putstr("ls: ");
	ft_putstr(name);
	ft_putstr(": Permission denied");
	write(1, "\n", 1);
}

void	print_dirname(char *dirname)
{
	//write(1, "\n", 1);
	ft_putstr(dirname);
	ft_putstr(":");
//	write(1, "\n", 1);
}

void	print_filename(struct stat *stats, char *name)
{
	char	linkname[255];

	ft_memset(linkname, '\0', sizeof(linkname));
	if (S_ISLNK(stats->st_mode))
	{
		space_after_str(name);
		space_after_str("->");
		if (!(readlink(name, linkname, stats->st_size)))
			strerror(errno);
		ft_putstr(linkname);
	}
	else
		ft_putstr(name);
	//write(1, "\n", 1);
}
