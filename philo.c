#include "philo.h"

bool validation(char **argv)
{
	return (1);
}

// void	finish_routine(t_philo *philo, int philo_num)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philo_num)
// 	{
// 		pthread_mutex_destroy(philo[i].fork1_mutex);
// 		i++;
// 	}
// 	pthread_mutex_destroy(philo[0].print_mutex);
// 	free(philo);
// 	exit(0);
// }

t_parse parse(char **argv)
{
	t_parse	parse;

	if (argv[5])
		parse.eat_num = ft_atoi(argv[5]);
	else
		parse.eat_num = -1;
	parse.philo_num = ft_atoi(argv[1]);
	parse.die_time = ft_atoi(argv[2]);
	parse.eat_time = ft_atoi(argv[3]);
	parse.sleep_time = ft_atoi(argv[4]);
	return (parse);
}

t_philo	*init(t_parse parse)
{
	int				i;
	t_philo			*philo;
	pthread_mutex_t	print_mutex;

	i = 0;
	philo = (t_philo *)malloc(parse.philo_num * sizeof(t_philo));
//	pthread_mutex_init(&print_mutex, NULL);
	while (i < parse.philo_num)
	{
		philo[i].eat_num = parse.eat_num;
		philo[i].die_time = parse.die_time;
		philo[i].eat_time = parse.eat_time;
		philo[i].philo_num = parse.philo_num;
		philo[i].sleep_time = parse.sleep_time;
		pthread_mutex_init(&philo[i].fork1_mutex, NULL);
		if (i == parse.philo_num - 1)
			philo[i].fork2_mutex = &philo[0].fork1_mutex;
		else
			philo[i].fork2_mutex = &philo[i + 1].fork1_mutex;
		i++;	
	}
	return (philo);
}

void	create_threads(t_philo *philo, int philo_num)
{
	int			i;
	pthread_t	*thread;

	i = 0;
	thread = (pthread_t *)malloc(philo_num * sizeof(pthread_t));
	while (i < philo_num)
	{
		philo[i].philo = i + 1;
		philo[i].start_time = get_time();
		philo[i].last_eat_time = philo[i].start_time;
		if (pthread_create(&thread[i], NULL,
			(void *(*)(void *))routine, (void *)&philo[i]))
			write(2, "Can't create thread\n", 20);
		i++;
	}
	while (--i > 0)
		pthread_join(thread[i], NULL);
	free(thread);
//	finish_routine(philo, philo_num);
}

int	main(int argc, char **argv)
{
	t_parse	data;
	t_philo *philo;

	if (argc < 5 || argc > 6)
		write(2, "Wrong number of arguments\n", 26);
	if (!validation(argv))
		write(2, "Penis\n", 6);	
	data = parse(argv);
	philo = init(data);
	create_threads(philo, data.philo_num);
	return (0);
}
