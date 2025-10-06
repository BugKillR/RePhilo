#include "philo.h"

long	ft_atol(const char *num)
{
	long	res;
	long	sign;
	long	i;

	res = 0;
	sign = 1;
	i = 0;
	while (num[i] && num[i] == ' ')
		i++;
	if (num[i] == '-' || num[i] == '+')
	{
		if (num[i] == '-')
			sign *= -1;
		i++;
	}
	while ('0' <= num[i] && num[i] <= '9')
	{
		res = (res * 10) + (num[i] - '0');
		i++;
	}
	return (res * sign);
}

static int	set_start_time(t_settings *set)
{
	if (gettimeofday(&(*set).start_time, NULL) != 0)
		return (1);
	return (0);
}

int	settings_init(t_settings *set, int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (printf("Invalid Argument Count!\n"), 1);
	(*set).number_of_philo = ft_atol(argv[1]);
	if ((*set).number_of_philo <= 0)
		return (printf("Number of philosophers can't be negative!\n"), 1);
	(*set).time_to_die = ft_atol(argv[2]);
	if ((*set).time_to_die <= 0)
		return (printf("Time to die must be higher than 0!\n"), 1);
	(*set).time_to_eat = ft_atol(argv[3]);
	if ((*set).time_to_eat <= 0)
		return (printf("Time to eat must be higher than 0!\n"), 1);
	(*set).time_to_sleep = ft_atol(argv[4]);
	if ((*set).time_to_sleep <= 0)
		return (printf("Time to sleep must be higher than 0!\n"), 1);
	if (argc == 5)
		(*set).max_eat_count = -1;
	else if (argc == 6)
	{
		(*set).max_eat_count = ft_atol(argv[5]);
		if ((*set).max_eat_count <= 0)
			return (printf("Number of times each philo must eat can't\n"), 1);
	}
	if (set_start_time(set))
		return (1);
	return (0);
}
