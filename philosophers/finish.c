/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:05:26 by akliek            #+#    #+#             */
/*   Updated: 2021/09/17 16:41:57 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	alredy_finished(t_philo *philo, int i)
{
	while (i < philo->philo_num)
	{
		if (philo[i].eat_num != 0)
			return (i);
		i++;
	}
	return (i);
}

void	eat_num_check(t_philo **philo)
{
	int	i;

	i = 0;
	while (1)
	{
		i = alredy_finished(*philo, i);
		if (i == (*philo)->philo_num)
		{
			pthread_mutex_unlock((*philo)->end_mutex);
			return ;
		}
	}
}

void	death_check(t_philo **philo)
{
	while (1)
	{
		if (get_time() - (*philo)->last_eat_time >= (*philo)->die_time)
		{
			print(*philo, DIED);
			pthread_mutex_unlock((*philo)->end_mutex);
		}
	}
}

void	finish(t_philo *philo, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_destroy(&philo[i].fork1_mutex);
		i++;
	}
	pthread_mutex_destroy(philo[0].print_mutex);
	free(philo->end_mutex);
	free(philo);
}
