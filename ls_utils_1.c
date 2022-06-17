/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:03:44 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/17 16:37:54 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	write_args_long(t_file arr, t_data *info)
{
//	if (info->arg_count < 2)
	//	print_dirname(arr.name);
	print_rights(&arr.stats, &arr);
	print_links(&arr.stats, info->padding[0]);
	print_users(&arr.stats);
	if (arr.is_device == 1)
	{
		print_major_and_minor(&arr.stats);
	}
	else
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
	ft_putstr(dirname);
	ft_putstr(":");
}

void	print_filename(struct stat *stats, char *name)
{
	char	linkname[MAX_NAME_LEN];

	ft_memset(linkname, '\0', ft_strlen(linkname));
	ft_strcat(linkname, name);
	if (S_ISLNK(stats->st_mode))
	{
		space_after_str(name);
		space_after_str("->");
		if (readlink(name, linkname, stats->st_size))
			ft_putstr(linkname);
	}
	else
		ft_putstr(name);
}

void	print_from_string(char *str, int start, int n)
{
	char	*temp;

	temp = str;
	while (n > 0)
	{
		write(1, &temp[start], 1);
		start++;
		n--;
	}
	write(1, " ", 1);
}