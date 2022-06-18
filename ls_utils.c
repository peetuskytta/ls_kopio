/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:05:23 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/18 09:18:35 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Writes short output.
*/
void	print_short(t_file *arr, int f_count)
{
	int	i;

	i = 0;
	while (i < f_count)
	{
		ft_putstr(arr[i].name);
		if (i != f_count - 1)
			write(1, "\n", 1);
		i++;
	}
}

/*
**	Utility function to write from string[start] n amount of characters.
**	Used in long print time output. Adds extra whitespace after the output.
*/
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

/*
**	Utility function to check how many arguments are files and directories.
**	Used in counters and to define break from loops.
*/
void	count_files_directories(t_file *arr, t_data *info, int i)
{
	while (i < info->arg_count)
	{
		if (arr[i].file_ok == TRUE)
		{
			if (S_ISDIR(arr[i].stats.st_mode))
				info->f_d_count[0]++;
			if (!(S_ISDIR(arr[i].stats.st_mode)))
				info->f_d_count[1]++;
		}
		i++;
	}
}

/*
**	Utility function to write space after a string.
*/
void	space_after_str(char *str)
{
	ft_putstr(str);
	ft_putstr(" ");
}

/*
**	Counter returning the number of files in a folder which is used
**	to allocate enough space for the array of structs.
*/
int	file_count(t_data *info, const char *name)
{
	DIR				*d;
	struct dirent	*entity;
	int				count;

	count = 0;
	d = opendir(name);
	if (d == NULL)
		return (0);
	entity = readdir(d);
	while (entity != NULL)
	{
		if (entity->d_name[0] != '.' || \
			(entity->d_name[0] == '.' && info->f_all == 1))
			count++;
		entity = readdir(d);
	}
	closedir(d);
	return (count);
}
