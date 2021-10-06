/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:42:07 by akliek            #+#    #+#             */
/*   Updated: 2021/10/06 11:45:20 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_parse	parse(char **argv)
{
	t_parse	parse;

	if (argv[5])
		parse.eat_num = atol(argv[5]);
	else
		parse.eat_num = -1;
	parse.philo_num = atol(argv[1]);
	parse.die_time = atol(argv[2]);
	parse.eat_time = atol(argv[3]);
	parse.sleep_time = atol(argv[4]);
	return (parse);
}

static void	wait_end(t_philo **philo)
{
	int	i;

	while (*(*philo)->dead == 0)
	{
		i = 0;
		while ((*philo)[i].eat_num == 0 && i < (*philo)->philo_num)
			i++;
		if (i == (*philo)->philo_num)
			break ;
	}
}

static t_philo	*create_threads(t_philo *philo, int philo_num)
{
	int			i;
	pthread_t	thread;

	i = 0;
	while (i < philo_num)
	{
		philo[i].index = i + 1;
		if (pthread_create(&thread, NULL,
				(void *(*)(void *))prepare_routine, (void *)&philo[i]))
			write(2, "Can't create thread\n", 20);
		pthread_detach(thread);
		i++;
	}
	if (pthread_create(&thread, NULL,
			(void *(*)(void *))finish_check, (void *)&philo))
		write(2, "Can't create thread\n", 20);
	pthread_detach(thread);
	wait_end(&philo);
	usleep(1000000);
	return (philo);
}

int	main(int argc, char **argv)
{
	t_parse	data;
	t_philo	*philo;

	if (!validation(argc, argv))
		return (-1);
	data = parse(argv);
	if (data.philo_num == 0)
		return (0);
	philo = init(data);
	philo = create_threads(philo, data.philo_num);
	clean_data(philo);
	return (0);
}
