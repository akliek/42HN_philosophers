#include "philo.h"

// void	my_sleep(unsigned long sleep_time, unsigned long start_time)
// {
// 	unsigned long current_time;

// 	current_time = get_time();
// 	while (current_time - start_time < sleep_time)
// 		current_time = get_time();
// }

// unsigned long	get_time(void)
// {
// 	struct timeval time;

// 	gettimeofday(&time, NULL);
// 	return (time.tv_sec * 1000 + time.tv_usec / 1000);
// }

// unsigned long	timestamp(unsigned long start_time)
// {
// 	return (get_time() - start_time);
// }

// int main()
// {
//     unsigned long   start;

//     start = get_time();
//     my_sleep(4, start);
//     printf("%ld\n", timestamp(start));
// }