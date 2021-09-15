#include "philo.h"

pthread_mutex_t	print_mutex;

void	print(t_philo *philo, t_status status)
{
	pthread_mutex_lock(&print_mutex);
	if (status == DIED)
		printf("%ld %d died\n", timestamp(philo->start_time), philo->philo);
	else if (status == EATING)
	{
		printf("%ld %d has taken a fork\n", timestamp(philo->start_time), philo->philo);
		printf("%ld %d is eating\n", timestamp(philo->start_time), philo->philo);
		pthread_mutex_unlock(&print_mutex);
	}
	else if (status == SLEEPING)
	{
		printf("%ld %d is sleeping\n", timestamp(philo->start_time), philo->philo);
		pthread_mutex_unlock(&print_mutex);
	}
	else if (status == THINKING)
	{
		printf("%ld %d is thinking\n", timestamp(philo->start_time), philo->philo);
		pthread_mutex_unlock(&print_mutex);
	}
	else if (status == FORK)
	{
		printf("%ld %d has taken a fork\n", timestamp(philo->start_time), philo->philo);
		pthread_mutex_unlock(&print_mutex);
	}
}

void	death_check(t_philo **philo)
{
	while (1)
	{
		if (get_time() - (*philo)->last_eat_time >= (*philo)->die_time)
		{
			print(*philo, DIED);
			exit(0);
		}
	}
}

void	thinking(t_philo *philo)
{
	print(philo, THINKING);
	if (philo->eat_num != 0)
		eating(philo);
}

void	sleeping(t_philo *philo)
{
	useconds_t	time;

	print(philo, SLEEPING);
	my_sleep(philo->sleep_time, get_time());
	thinking(philo);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->fork2_mutex);
	print(philo, FORK);
	pthread_mutex_lock(&philo->fork1_mutex);
	print(philo, EATING);
	my_sleep(philo->sleep_time, get_time());
	philo->last_eat_time = get_time();
	philo->eat_num--;
	pthread_mutex_unlock(philo->fork2_mutex);
	pthread_mutex_unlock(&philo->fork1_mutex);
	sleeping(philo);
}

void	routine(t_philo *philo)
{
	pthread_t	thread;

	pthread_mutex_init(&print_mutex, NULL);
	if(pthread_create(&thread, NULL,
		(void *(*)(void *))death_check, (void *)&philo))
		write(2, "Can't create thread\n", 20);
	if (philo->philo % 2 == 0)
		eating(philo);
	else
		sleeping(philo);
}
