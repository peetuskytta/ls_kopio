/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_long_prints.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:01:24 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/21 14:06:39 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Outputs the total blocks number for a folder.
*/
static void	print_block_total(t_file *arr, int f_count)
{
	int	i;
	int	blocks;

	blocks = 0;
	i = 0;
	while (f_count > i)
	{
		blocks = blocks + arr[i].stats.st_blocks;
		i++;
	}
	if (f_count != 0)
	{
		write(1, "total ", 6);
		ft_putnbr_endl(blocks);
	}
}

/*
**	Outputs filename at the end of long format and adds link path if
**	it is a link.
*/
static void	print_filename(struct stat *stats, char *filename, char *link)
{
	if (S_ISLNK(stats->st_mode))
	{
		space_after_str(filename);
		write(1, "-> ", 3);
		write(1, link, ft_strlen(link));
	}
	else
		write(1, filename, ft_strlen(filename));
}

/*
**	Utility function to output the major and minor number for character and
**	block special devices.
*/
static void	print_major_and_minor(struct stat *stats)
{
	int	major;
	int	minor;

	major = 0;
	minor = 0;
	major = return_major_or_minor(stats->st_rdev, 1);
	minor = return_major_or_minor(stats->st_rdev, 0);
	ft_putnbr(major);
	write(1, ", ", 2);
	ft_putnbr(minor);
	write(1, " ", 1);
}

/*
**	Executes the long output one by one for argument input.
*/
void	write_args_long(t_file arr)
{
	print_rights(&arr.stats, &arr);
	print_links_nbr(&arr.stats);
	print_users(&arr.stats);
	if (arr.is_device == 1)
		print_major_and_minor(&arr.stats);
	else
		print_file_size(&arr.stats);
	print_mod_time(&arr.stats);
	print_filename(&arr.stats, arr.name, arr.link_path);
	write(1, "\n", 1);
}

/*
**	Executes the long output one by one for no argument inputs.
*/
void	write_long_output(t_file *arr, int f_count, int i)
{
	print_block_total(arr, f_count);
	while (f_count > i)
	{
		print_rights(&arr[i].stats, &arr[i]);
		print_links_nbr(&arr[i].stats);
		print_users(&arr[i].stats);
		if (arr[i].is_device == 1)
			print_major_and_minor(&arr[i].stats);
		else
			print_file_size(&arr[i].stats);
		print_mod_time(&arr[i].stats);
		print_filename(&arr[i].stats, arr[i].name, arr[i].link_path);
		if (i != f_count - 1)
			write(1, "\n", 1);
		i++;
	}
}
