/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 11:06:31 by akliek            #+#    #+#             */
/*   Updated: 2021/10/05 18:40:18 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	mutex_init(t_philo **philo, int i)
{
	if (i == 0)
	{
		(*philo)[i].print_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init((*philo)[i].print_mutex, NULL);
	}
	else
		(*philo)[i].print_mutex = (*philo)[0].print_mutex;
	pthread_mutex_init(&(*philo)[i].fork1_mutex, NULL);
	if (i == (*philo)[i].philo_num - 1)
		(*philo)[i].fork2_mutex = &(*philo)[0].fork1_mutex;
	else
		(*philo)[i].fork2_mutex = &(*philo)[i + 1].fork1_mutex;
}

static t_philo	*init_chekers(t_philo *philo, int i)
{
	if (i == 0)
	{
		philo[i].wait_threads = (int *)malloc(sizeof(int));
		*philo[i].wait_threads = 0;
		philo[i].dead = (bool *)malloc(sizeof(bool));
		*philo[i].dead = 0;
	}
	else
	{
		philo[i].wait_threads = philo[0].wait_threads;
		*philo[i].wait_threads = 0;
		philo[i].dead = philo[0].dead;
		*philo[i].dead = 0;
	}
	return (philo);
}

t_philo	*init(t_parse parse)
{
	int				i;
	t_philo			*philo;

	i = 0;
	philo = (t_philo *)malloc(parse.philo_num * sizeof(t_philo));
	while (i < parse.philo_num)
	{
		philo[i].index = 0;
		philo[i].start_time = 0;
		philo[i].last_eat_time = 0;
		philo[i].eat_num = parse.eat_num;
		philo[i].die_time = parse.die_time;
		philo[i].eat_time = parse.eat_time;
		philo[i].philo_num = parse.philo_num;
		philo[i].sleep_time = parse.sleep_time;
		mutex_init(&philo, i);
		philo = init_chekers(philo, i);
		i++;
	}
	return (philo);
}
