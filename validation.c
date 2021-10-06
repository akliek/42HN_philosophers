/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:19:10 by akliek            #+#    #+#             */
/*   Updated: 2021/09/17 16:51:32 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_positive_number(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s < 48 || *s > 57)
			return (0);
		s++;
	}
	return (1);
}

bool	validation(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		write(2, "Wrong number of arguments\n", 26);
		return (0);
	}
	while (argv[i])
	{
		if (!is_positive_number(argv[i]))
		{
			write(2, "Wrong argument\n", 15);
			return (0);
		}
		i++;
	}
	return (1);
}
