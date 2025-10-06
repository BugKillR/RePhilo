#include "philo.h"

static void	info_free_helper2(t_info **info_arr)
{
	if (info_arr[0]->count_of_complete)
		free(info_arr[0]->count_of_complete);
	if (info_arr[0]->counter_lock)
	{
		pthread_mutex_destroy(info_arr[0]->counter_lock);
		free(info_arr[0]->counter_lock);
	}
	if (info_arr[0]->died_counter)
	{
		pthread_mutex_destroy(info_arr[0]->died_counter);
		free(info_arr[0]->died_counter);
	}
}

static void	info_free_helper(t_info **info_arr)
{
	int	i;

	if (info_arr[0]->all_mutexes)
	{
		i = 0;
		while (i < info_arr[0]->set.number_of_philo)
			pthread_mutex_destroy(&(info_arr[0]->all_mutexes)[i++]);
		free(info_arr[0]->all_mutexes);
	}
	if (info_arr[0]->printf_lock)
	{
		pthread_mutex_destroy(info_arr[0]->printf_lock);
		free(info_arr[0]->printf_lock);
	}
	if (info_arr[0]->is_any_died)
		free(info_arr[0]->is_any_died);
	info_free_helper2(info_arr);
}

void	info_free_on_error(t_info **info_arr, int count)
{
    int i;

	if ((!info_arr || !info_arr[0]))
		return ;
	info_free_helper(info_arr);
	i = 0;
	while (i < count)
	{
		if (info_arr[i])
			free(info_arr[i]);
		i++;
	}
	free(info_arr);
}

void	free_forks(pthread_mutex_t *forks)
{
	if(forks)
		free(forks);
}
