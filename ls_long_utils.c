/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:12:43 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/10 14:23:27 by pskytta          ###   ########.fr       */
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
	if (S_ISLNK(mode))
		str[0] = 'l';
	if (S_ISREG(mode))
		str[0] = '-';
	if (S_ISDIR(mode))
		str[0] = 'd';
	if (S_ISCHR(mode))
		str[0] = 'c';
	if (S_ISBLK(mode))
		str[0] = 'b';
	if (S_ISSOCK(mode))
		str[0] = 's';
	if (S_ISFIFO(mode))
		str[0] = 'p';
}

void	print_rights(struct stat *stats)
{
	char	str[11];

	ft_strclr(str);
	ft_strcpy(str, "----------");
	set_file_type(stats->st_mode, str);
	check_user(stats->st_mode, str);
	check_group(stats->st_mode, str);
	check_other(stats->st_mode, str);
	ft_putstr(str);
	ft_putchar(' ');
}
