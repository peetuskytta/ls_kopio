/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:01:48 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/18 00:22:30 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	check_user(int mode, char *str)
{
	if (mode & S_IRUSR)
		str[1] = 'r';
	if (mode & S_IWUSR)
		str[2] = 'w';
	if ((mode & S_IXUSR) && (mode & S_ISUID))
		str[3] = 's';
	else if (!(mode & S_IXUSR) && (mode & S_ISUID))
		str[3] = 'S';
	else if (mode & S_IXUSR)
		str[3] = 'x';
}

static void	check_group(int mode, char *str)
{
	if (mode & S_IRGRP)
		str[4] = 'r';
	if (mode & S_IWGRP)
		str[5] = 'w';
	if ((mode & S_IXGRP) && (mode & S_ISGID))
		str[6] = 's';
	else if (!(mode & S_IXGRP) && (mode & S_ISGID))
		str[6] = 'S';
	else if (mode & S_IXGRP)
		str[6] = 'x';
}

static void	check_other(int mode, char *str)
{
	if (mode & S_IROTH)
		str[7] = 'r';
	if (mode & S_IWOTH)
		str[8] = 'w';
	if ((mode & S_IXOTH) && (mode & S_ISVTX))
		str[9] = 't';
	else if (!(mode & S_IXOTH) && (mode & S_ISVTX))
		str[9] = 'T';
	else if (mode & S_IXOTH)
		str[9] = 'x';
}

void	set_file_type(char *str, struct stat stats, t_file *arr)
{
	arr->is_device = 0;
	if (S_ISDIR(stats.st_mode))
		str[0] = 'd';
	else if (S_ISLNK(stats.st_mode))
		str[0] = 'l';
	else if (S_ISBLK(stats.st_mode))
	{
		arr->is_device = 1;
		str[0] = 'b';
	}
	else if (S_ISCHR(stats.st_mode))
	{
		arr->is_device = 1;
		str[0] = 'c';
	}
	else if (S_ISSOCK(stats.st_mode))
		str[0] = 's';
	else if (S_ISFIFO(stats.st_mode))
		str[0] = 'p';
}

void	print_rights(struct stat *stats, t_file *arr)
{
	char	str[11];

	ft_strclr(str);
	ft_strcpy(str, "----------");
	set_file_type(str, *stats, arr);
	check_user(stats->st_mode, str);
	check_group(stats->st_mode, str);
	check_other(stats->st_mode, str);
	ft_putstr(str);
	ft_putchar(' ');
}
