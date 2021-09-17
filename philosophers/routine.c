/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:45:45 by akliek            #+#    #+#             */
/*   Updated: 2021/09/17 18:22:38 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	print(philo, THINKING);
	if (philo->eat_num != 0)
		eating(philo);
}

void	sleeping(t_philo *philo)
{
	my_sleep(philo->sleep_time, get_time());
	thinking(philo);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->fork2_mutex);
	print(philo, FORK);
	pthread_mutex_lock(&philo->fork1_mutex);
	print(philo, EATING);
	my_sleep(philo->eat_time, get_time());
	philo->last_eat_time = get_time();
	philo->eat_num--;
	print(philo, SLEEPING);
	pthread_mutex_unlock(philo->fork2_mutex);
	pthread_mutex_unlock(&philo->fork1_mutex);
	sleeping(philo);
}

void	routine(t_philo *philo)
{
	pthread_t	thread;

	*philo->wait_threads += 1;
	while (1)
	{
		if (*philo->wait_threads == philo->philo_num)
			break ;
	}
	philo->start_time = get_time();
	philo->last_eat_time = philo->start_time;
	if (pthread_create(&thread, NULL,
			(void *(*)(void *))death_check, (void *)&philo))
		write(2, "Can't create thread\n", 20);
	if (philo->index % 2 != 0)
		thinking(philo);
	else
		sleeping(philo);
}
