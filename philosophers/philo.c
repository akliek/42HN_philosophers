/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:42:07 by akliek            #+#    #+#             */
/*   Updated: 2021/09/17 16:44:44 by akliek           ###   ########.fr       */
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

static void	mutex_init(t_philo **philo, int i)
{
	if (i == 0)
	{
		(*philo)[i].end_mutex = malloc(sizeof(pthread_mutex_t));
		(*philo)[i].print_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init((*philo)[i].print_mutex, NULL);
		pthread_mutex_init((*philo)[i].end_mutex, NULL);
		pthread_mutex_lock((*philo)[i].end_mutex);
	}
	else
	{
		(*philo)[i].wait_threads = (*philo)[0].wait_threads;
		(*philo)[i].print_mutex = (*philo)[0].print_mutex;
		(*philo)[i].end_mutex = (*philo)[0].end_mutex;
	}
	pthread_mutex_init(&(*philo)[i].fork1_mutex, NULL);
	if (i == (*philo)[i].philo_num - 1)
		(*philo)[i].fork2_mutex = &(*philo)[0].fork1_mutex;
	else
		(*philo)[i].fork2_mutex = &(*philo)[i + 1].fork1_mutex;
}

static t_philo	*init(t_parse parse)
{
	int				i;
	t_philo			*philo;

	i = 0;
	philo = (t_philo *)malloc(parse.philo_num * sizeof(t_philo));
	while (i < parse.philo_num)
	{
		philo[i].eat_num = parse.eat_num;
		philo[i].die_time = parse.die_time;
		philo[i].eat_time = parse.eat_time;
		philo[i].philo_num = parse.philo_num;
		philo[i].sleep_time = parse.sleep_time;
		mutex_init(&philo, i);
		if (i == 0)
		{
			philo[i].wait_threads = (int *)malloc(sizeof(int));
			*philo[i].wait_threads = 0;
		}
		else
			philo[i].wait_threads = philo[0].wait_threads;
		i++;
	}
	return (philo);
}

static void	create_threads(t_philo *philo, int philo_num)
{
	int			i;
	pthread_t	thread;

	i = 0;
	while (i < philo_num)
	{
		philo[i].index = i + 1;
		if (pthread_create(&thread, NULL,
				(void *(*)(void *))routine, (void *)&philo[i]))
			write(2, "Can't create thread\n", 20);
		pthread_detach(thread);
		i++;
	}
	if (pthread_create(&thread, NULL,
			(void *(*)(void *))eat_num_check, (void *)&philo))
		write(2, "Can't create thread\n", 20);
	pthread_detach(thread);
	pthread_mutex_lock(philo->end_mutex);
	finish(philo, philo->philo_num);
}

int	main(int argc, char **argv)
{
	t_parse	data;
	t_philo	*philo;

	if (!validation(argc, argv))
		return (-1);
	data = parse(argv);
	philo = init(data);
	create_threads(philo, data.philo_num);
	return (0);
}
