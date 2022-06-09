/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:12:43 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/09 17:03:13 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	check_user(int mode, char *str)
{
	if (mode & S_IRUSR)
		str[1] = 'r';
	if (mode & S_IWUSR)
		str[2] = 'w';
	if (mode & S_IXUSR)
		str[3] = 'x';
}

static void	check_group(int mode, char *str)
{
	if (mode & S_IRGRP)
		str[4] = 'r';
	if (mode & S_IWGRP)
		str[5] = 'w';
	if (mode & S_IXGRP)
		str[6] = 'x';
}

static void	check_other(int mode, char *str)
{
	if (mode & S_IROTH)
		str[7] = 'r';
	if (mode & S_IWOTH)
		str[8] = 'w';
	if (mode & S_IXOTH)
		str[9] = 'x';
}

void	set_file_type(int mode, char *str)
{
	if (mode & S_IFLNK)
		str[0] = 'l';
	if (mode & S_IFREG)
		str[0] = '-';
	if (mode & S_IFDIR)
		str[0] = 'd';
}

void	print_rights(struct stat *stats)
{
	char	str[11];

	ft_strncpy(str, "----------\0", 11);
	set_file_type(stats->st_mode, str);
	check_user(stats->st_mode, str);
	check_group(stats->st_mode, str);
	check_other(stats->st_mode, str);
	ft_putstr(str);
	ft_putchar(' ');
}
