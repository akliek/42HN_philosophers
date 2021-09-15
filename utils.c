#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

unsigned long	timestamp(unsigned long start_time)
{
	return (get_time() - start_time);
}

void	my_sleep(unsigned long sleep_time, unsigned long start_time)
{
	unsigned long current_time;

	current_time = get_time();
	while (current_time - start_time < sleep_time)
		current_time = get_time();
}

int	is_number(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s < 48 || *s > 57)
			return (0);
		s++;
	}
	return (1);
}

long	ft_atoi(const char *str)
{
	int			sign;
	long long	res;

	sign = 1;
	res = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && *str >= 48 && *str <= 57)
	{
		res *= 10;
		res += *str - 48;
		str++;
	}
	return (sign * res);
}
