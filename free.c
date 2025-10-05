#include "philo.h"

void	info_free_on_error(t_info **info_arr, int count)
{
    int i;

	if (!info_arr)
		return ;
	if (info_arr[0]->all_mutexes)
		free(info_arr[0]->all_mutexes);
	if (info_arr[0]->printf_lock)
		free(info_arr[0]->printf_lock);
	if (info_arr[0]->is_any_died)
		free(info_arr[0]->is_any_died);
	i = 0;
	while (i < count)
	{
		if (info_arr[i])
			free(info_arr[i]);
		i++;
	}
	free(info_arr);
}

void	philo_free_on_error(pthread_t **philo_arr)
{
    if (!philo_arr)
		return ;
	free(philo_arr);
}
