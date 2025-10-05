#include "philo.h"

void	fork_message(long ms_passed, int philo_id, t_info info)
{
	pthread_mutex_lock(info.printf_lock);
	printf("%ld %d has taken a fork\n", ms_passed, philo_id);
	pthread_mutex_unlock(info.printf_lock);
}

void	eat_message(long ms_passed, int philo_id, t_info info)
{
	pthread_mutex_lock(info.printf_lock);
	printf("%ld %d is eating\n", ms_passed, philo_id);
	pthread_mutex_unlock(info.printf_lock);
}

void	sleep_message(long ms_passed, int philo_id, t_info info)
{
	pthread_mutex_lock(info.printf_lock);
	printf("%ld %d is sleeping\n", ms_passed, philo_id);
	pthread_mutex_unlock(info.printf_lock);
}

void	think_message(long ms_passed, int philo_id, t_info info)
{
	pthread_mutex_lock(info.printf_lock);
	printf("%ld %d is thinking\n", ms_passed, philo_id);
	pthread_mutex_unlock(info.printf_lock);
}

void	died_message(long ms_passed, int philo_id, t_info info)
{
	pthread_mutex_lock(info.printf_lock);
	printf("%ld %d died\n", ms_passed, philo_id);
	pthread_mutex_unlock(info.printf_lock);
}
