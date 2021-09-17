/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:02:45 by akliek            #+#    #+#             */
/*   Updated: 2021/09/17 16:54:09 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, t_status status)
{
	pthread_mutex_lock(philo->print_mutex);
	if (status == DIED)
	{
		printf("%ld %d died",
			timestamp(philo->start_time), philo->index);
		return ;
	}
	else if (status == EATING)
	{
		printf("%ld %d has taken a fork\n",
			timestamp(philo->start_time), philo->index);
		printf("%ld %d is eating\n",
			timestamp(philo->start_time), philo->index);
	}
	else if (status == SLEEPING)
		printf("%ld %d is sleeping\n",
			timestamp(philo->start_time), philo->index);
	else if (status == THINKING)
		printf("%ld %d is thinking\n",
			timestamp(philo->start_time), philo->index);
	else if (status == FORK)
		printf("%ld %d has taken a fork\n",
			timestamp(philo->start_time), philo->index);
	pthread_mutex_unlock(philo->print_mutex);
}
