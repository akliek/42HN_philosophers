#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_status
{
	NONE,
	DIED,
	SLEEPING,
	EATING,
	THINKING,
	FORK
}			t_status;

typedef	struct s_parse
{
	int				eat_num;
	int				philo_num;
	unsigned long	die_time;
	unsigned long	eat_time;
	unsigned long	sleep_time;
}			t_parse;


typedef struct s_philo
{
	int				philo;
	int				eat_num;
	int				philo_num;
	unsigned long	die_time;
	unsigned long	eat_time;
	unsigned long	sleep_time;
	unsigned long	start_time;
	unsigned long	last_eat_time;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	fork1_mutex;
	pthread_mutex_t	*fork2_mutex;
}			t_philo;

void			routine(t_philo *philo);
void			eating(t_philo *philo);
void			sleepin(t_philo *philo);
void			thinking(t_philo *philo);
void			my_sleep(unsigned long sleep_time, unsigned long start_time);
long			ft_atoi(const char *str);
void			finish_routine(t_philo *philo, int philo_num);
unsigned long	get_time(void);
unsigned long	timestamp(unsigned long start_time);

#endif
