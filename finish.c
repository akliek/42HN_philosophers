/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:05:26 by akliek            #+#    #+#             */
/*   Updated: 2021/10/06 11:25:03 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	is_dead(t_philo **philo, int i)
{
	pthread_mutex_lock((*philo)->print_mutex);
	printf("%ld %d died\n",
		timestamp((*philo)[i].start_time), (*philo)[i].index);
	*(*philo)->dead = 1;
	return ;
}

void	finish_check(t_philo **philo)
{
	int	i;
	int	num_eaten;

	while (1)
	{
		if (*(*philo)->wait_threads != (*philo)->philo_num)
			continue ;
		i = 0;
		num_eaten = 0;
		while (i < (*philo)->philo_num)
		{
			if ((*philo)[i].die_time - (get_time()
				- (*philo)[i].last_eat_time) <= 0
				&& (*philo)[i].eat_num && (*philo)[i].start_time
				&& (*philo)[i].last_eat_time)
				return (is_dead(philo, i));
			else if ((*philo)[i].eat_num == 0)
				num_eaten++;
			i++;
		}
		if (num_eaten == (*philo)->philo_num)
			return ;
	}
}

void	clean_data(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo_num)
	{
		pthread_mutex_unlock(&philo[i].fork1_mutex);
		pthread_mutex_destroy(&philo[i].fork1_mutex);
		i++;
	}
	pthread_mutex_destroy(philo[0].print_mutex);
	free(philo[0].print_mutex);
	free(philo[0].wait_threads);
	free(philo[0].dead);
	free(philo);
}
