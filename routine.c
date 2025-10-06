#include "philo.h"

static long	calculate_time(struct timeval start)
{
	struct timeval	current;
	long			elapsed_ms;

	gettimeofday(&current, NULL);
	elapsed_ms = (current.tv_sec - start.tv_sec) * 1000
			+	(current.tv_usec - start.tv_usec) / 1000;
	return (elapsed_ms);
}

static int	is_any_died_check(t_info *info)
{
	pthread_mutex_lock((*info).died_counter);
	if (*((*info).is_any_died) > 0)
	{
		pthread_mutex_unlock((*info).died_counter);
		return (1);
	}
	pthread_mutex_unlock((*info).died_counter);
	return (0);
}

static int	eat_fork_lock(t_info *info, int left, int right)
{
	if ((*info).index_of_philo % 2 == 0)
	{	
		pthread_mutex_lock(&(*info).all_mutexes[right]);
		pthread_mutex_lock(&(*info).all_mutexes[left]);
		if (is_any_died_check(info))
		{
			pthread_mutex_unlock(&(*info).all_mutexes[right]);
			pthread_mutex_unlock(&(*info).all_mutexes[left]);
			return (1) ;
		}
		fork_message(calculate_time((*info).set.start_time), (*info).index_of_philo, *info);
	}	
	else
	{
		pthread_mutex_lock(&(*info).all_mutexes[left]);
		pthread_mutex_lock(&(*info).all_mutexes[right]);
		if (is_any_died_check(info))
		{	
			pthread_mutex_unlock(&(*info).all_mutexes[left]);
			pthread_mutex_unlock(&(*info).all_mutexes[right]);
			return (1);
		}
		fork_message(calculate_time((*info).set.start_time), (*info).index_of_philo, *info);
	}
	return (0);
}

static int	eat_fork_unlock(t_info *info, int left, int right, struct timeval *last_eat)
{
	pthread_mutex_unlock(&(*info).all_mutexes[left]);
	pthread_mutex_unlock(&(*info).all_mutexes[right]);
	gettimeofday(last_eat, NULL);
	if (is_any_died_check(info))
			return (1) ;
	think_message(calculate_time((*info).set.start_time), (*info).index_of_philo, *info);
	return (0);
}

static int	is_starved(t_info *info, struct timeval last_eat)
{
	if (calculate_time(last_eat) >= ((*info).set.time_to_die))
	{
		pthread_mutex_lock((*info).died_counter);
		*info->is_any_died = *info->is_any_died + 1;
		pthread_mutex_unlock((*info).died_counter);
		died_message(calculate_time((*info).set.start_time), (*info).index_of_philo, *info);
		return (1);
	}
	return (0);
}

static void	loop(t_info *info)
{
	struct timeval	last_eat;
	int				left;
	int				right;
	int				i;

	left = (*info).index_of_philo;
	right = ((*info).index_of_philo + 1) % (*info).set.number_of_philo;
	gettimeofday(&last_eat, NULL);
	i = 0;
	while (i < (*info).set.max_eat_count || (*info).set.max_eat_count == -1)
	{
		if (is_starved(info, last_eat))
			break;
		if (eat_fork_lock(info, left, right))
			break ;
		if (is_any_died_check(info))
			break ;
		eat_message(calculate_time((*info).set.start_time), ((*info).index_of_philo), *info);
		usleep((*info).set.time_to_eat * 1000);
		if (eat_fork_unlock(info, left, right, &last_eat))
			break ;
		if (is_any_died_check(info))
			break ;
		sleep_message(calculate_time((*info).set.start_time), ((*info).index_of_philo), *info);
		usleep((*info).set.time_to_sleep * 1000);
		if (is_any_died_check(info))
			break ;
		i++;
	}
	pthread_mutex_lock((*info).counter_lock);
	*((*info).count_of_complete) = *((*info).count_of_complete) + 1;
	pthread_mutex_unlock((*info).counter_lock);
}

void	*routine(void *arg)
{
    t_info	*info;

    info = (t_info *)arg;
    loop(info);
    return (NULL);
}