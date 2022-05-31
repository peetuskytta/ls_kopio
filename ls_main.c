/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:29:40 by pskytta           #+#    #+#             */
/*   Updated: 2022/05/30 18:29:40 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ls_check(char *str)
{
	if (str)
	{
		if (ft_strcmp(str, "ls") != 0)
		{
			ft_putstr("command not found: ");
			ft_putendl(str);
			exit(-1);
		}
	}
}

static void	args_check(int args)
{
	if (args < 2)
	{
		ft_putendl("usage: ./ft_ls <ls> <flags> <filename>");
		exit(-1);
	}
}

void	primary_checks(int args, char **str)
{
	args_check(args);
	ls_check(str[1]);
}

void	print_double(char **str)
{
	// reminder: DELETE THIS before submit
	size_t	i;

	i = 0;
	while (str[i] != NULL)
	{
		ft_putendl(str[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	*arr;

	arr = ft_memalloc(sizeof(t_data));
	primary_checks(argc, argv);
	handle_flags(arr, argv);

	printf("l: %d\na: %d\nr: %d\nR: %d\nt: %d\n", arr->flags[0], arr->flags[1], arr->flags[2], arr->flags[3], arr->flags[4]);
	printf("padding hd: %d\n", arr->padding[0]);
	printf("padding size: %d\n", arr->padding[1]);
	printf("files total: %d\n", arr->file_count);
	printf("argument total: %d\n", arr->arg_count);
	printf("flag arguments total: %d\n", arr->flag_count);

	if (argv[arr->arg_count] == NULL)
	{
		printf("do basic ls options\n");
		ls_driver(arr);
	}
	else
	{
		printf("do ls from argv\n");
		//list_driver();
	}


	printf("\nhenlo\n");
	free(arr);
	return (0);
}