/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_error_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:01:06 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/21 14:55:26 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ch_error(char c)
{
	ft_putstr("ls: illegal option -- ");
	write(1, &c, 1);
	write(1, "\n", 1);
	write(1, "usage: ./ft_ls [-larRt] [file ...]\n", 35);
	exit(1);
}

void	file_no_exist(char *str)
{
	write(1, "ls: ", 4);
	write(1, str, ft_strlen(str));
	write(1, ": ", 2);
	write(1, "No such file or directory\n", 26);
}

void	no_directory_access(char *name)
{
	write(1, "ls: ", 4);
	write(1, name, ft_strlen(name));
	write(1, ": Permission denied", 19);
	write(1, "\n", 1);
}
