/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:01:06 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/17 10:01:07 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ch_error(char c)
{
	ft_putstr("ls: illegal option -- ");
	ft_putchar(c);
	ft_putendl("");
	ft_putendl("usage: ./ft_ls [-larRt] [file ...]");
	exit(1);
}

void	command_not_found(char *str)
{
	ft_putstr("unknown command: ");
	ft_putendl(str);
	ft_putendl("please use <ls>");
	exit(1);
}

void	usage_error(void)
{
	ft_putendl("usage: <./ft_ls> <flags/filenames>");
	exit(1);
}
