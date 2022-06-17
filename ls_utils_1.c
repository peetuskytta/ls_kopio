/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:03:44 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/17 20:17:26 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	write_args_long(t_file arr)
{
	print_rights(&arr.stats, &arr);
	print_links(&arr.stats);
	print_users(&arr.stats);
	if (arr.is_device == 1)
		print_major_and_minor(&arr.stats);
	else
		print_file_size(&arr.stats);
	print_mod_time(&arr.stats);
	print_filename(&arr.stats, arr.name);
	ft_putchar('\n');
}

void	print_dirname(char *dirname)
{
	ft_putstr(dirname);
	ft_putstr(":");
}

void	print_filename(struct stat *stats, char *name)
{
	char	linkname[255];

	ft_memset(linkname, '\0', ft_strlen(linkname));
	//ft_strcat(linkname, name);
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
