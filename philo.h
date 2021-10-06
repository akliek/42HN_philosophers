/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:45:26 by akliek            #+#    #+#             */
/*   Updated: 2021/10/05 17:50:54 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

/*==========STATUS_STRUCT==========*/

typedef enum e_status
{
	DIED,
	SLEEPING,
	EATING,
	THINKING,
	FORK
}			t_status;

/*==========PARSE_DATA_STRUCT==========*/

typedef struct s_parse
{
	int				eat_num;
	int				philo_num;
	unsigned long	die_time;
	unsigned long	eat_time;
	unsigned long	sleep_time;
}			t_parse;

/*==========PHILOSOPHERS_DATA_STRUCT==========*/

typedef struct s_philo
{
	int				index;
	int				eat_num;
	int				philo_num;
	int				*wait_threads;
	bool			*dead;
	unsigned long	die_time;
	unsigned long	eat_time;
	unsigned long	sleep_time;
	unsigned long	start_time;
	unsigned long	last_eat_time;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	fork1_mutex;
	pthread_mutex_t	*fork2_mutex;
}			t_philo;

/*==========UTILS==========*/

long			atol(const char *str);
void			my_sleep(unsigned long sleep_time,
					unsigned long start_time);
unsigned long	get_time(void);
unsigned long	timestamp(unsigned long start_time);

/*==========VALIDATION==========*/

bool			validation(int argc, char **argv);

/*==========INIT==========*/

t_philo			*init(t_parse parse);

/*==========PRINT==========*/

void			print(t_philo *philo, t_status status);

/*==========FINISH_CHECK==========*/

void			clean_data(t_philo *philo);
void			finish_check(t_philo **philo);

/*==========ROUTINE==========*/

void			prepare_routine(t_philo *philo);

#endif
