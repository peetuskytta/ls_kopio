/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_with_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 21:32:28 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/06 21:32:28 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_with_flags(t_data *info)
{
	t_file	*arr;

	arr = read_dir_stream(info, ".", 0);
	sort_driver(arr, info);
	print_short(arr, info);
}