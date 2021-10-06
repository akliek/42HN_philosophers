/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:45:45 by akliek            #+#    #+#             */
/*   Updated: 2021/10/06 11:24:56 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status	sleeping(t_philo *philo)
{
	print(philo, SLEEPING);
	my_sleep(philo->sleep_time, get_time());
	return (THINKING);
}

static t_status	thinking(t_philo *philo)
{
	print(philo, THINKING);
	return (EATING);
}

static t_status	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork1_mutex);
	print(philo, FORK);
	pthread_mutex_lock(philo->fork2_mutex);
	print(philo, EATING);
	philo->last_eat_time = get_time();
	my_sleep(philo->eat_time, get_time());
	philo->eat_num--;
	pthread_mutex_unlock(&philo->fork1_mutex);
	pthread_mutex_unlock(philo->fork2_mutex);
	return (SLEEPING);
}

static	void	routine(t_philo *philo)
{
	t_status	status;

	if (philo->index % 2 != 0)
		status = THINKING;
	else
		status = SLEEPING;
	while (philo->eat_num != 0 && *philo->dead == 0)
	{
		if (status == THINKING)
			status = thinking(philo);
		else if (status == EATING)
		{
			usleep(42);
			status = eating(philo);
		}
		else if (status == SLEEPING)
			status = sleeping(philo);
	}
}

void	prepare_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	*philo->wait_threads += 1;
	pthread_mutex_unlock(philo->print_mutex);
	while (*philo->wait_threads != philo->philo_num)
		continue ;
	philo->start_time = get_time();
	philo->last_eat_time = philo->start_time;
	if (philo->eat_num == 0)
		return ;
	routine(philo);
}
