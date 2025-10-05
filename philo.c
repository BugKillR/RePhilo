#include "philo.h"

void init_info_arr_elems(t_info *info, t_settings set, int i, pthread_mutex_t *m)
{
    info->set = set;
    info->index_of_philo = i;
    info->all_mutexes = m;
}

pthread_mutex_t	*create_fork(t_settings set)
{
    pthread_mutex_t *m = malloc(sizeof(pthread_mutex_t) * set.number_of_philo);
    if (!m) return NULL;

    int i = 0;
    while (i < set.number_of_philo) {
        pthread_mutex_init(&m[i], NULL);
        i++;
    }
    return (m);
}

t_info **init_info_arr(t_settings set, pthread_mutex_t *m)
{
	t_info			**info_arr;
	pthread_mutex_t	*printf_lock;
	int				*is_any_died;
	int 			i;

    info_arr = malloc(sizeof(t_info *) * (set.number_of_philo + 1));
    if (!info_arr) 
		return (NULL);
    printf_lock = malloc(sizeof(pthread_mutex_t));
    if (!printf_lock)
		return (NULL);
    pthread_mutex_init(printf_lock, NULL);
    is_any_died = malloc(sizeof(int));
    *is_any_died = 0;
	i = 0;
    while (i < set.number_of_philo)
	{
        info_arr[i] = malloc(sizeof(t_info));
        if (!info_arr[i])
            return (info_free_on_error(info_arr, i), free(printf_lock), free(is_any_died), NULL);
        init_info_arr_elems(info_arr[i], set, i, m);
        info_arr[i]->printf_lock = printf_lock;
        info_arr[i]->is_any_died = is_any_died;
        i++;
    }
    return (info_arr[i] = NULL, info_arr);
}

void	init_program(t_settings set, pthread_t **philo_arr, t_info ***info_arr, pthread_mutex_t *m)
{
    *info_arr = init_info_arr(set, m);
    if (!*info_arr)
		return ;
    *philo_arr = malloc(sizeof(pthread_t) * set.number_of_philo);
    if (!*philo_arr)
	{
        info_free_on_error(*info_arr, set.number_of_philo);
        return ;
    }
}

void start_threads(pthread_t *philo_arr, t_info **info_arr, t_settings set)
{
    int i = 0;
    while (i < set.number_of_philo)
	{
        pthread_create(&philo_arr[i], NULL, &routine, (void *)info_arr[i]);
        i++;
    }
}

void join_all_threads(pthread_t *philo_arr, t_settings set)
{
    int i = 0;
    while (i < set.number_of_philo)
	{
        pthread_join(philo_arr[i], NULL);
        i++;
    }
}

void clean_mutexes(t_info *info)
{
    int i = 0;
    while (i < info->set.number_of_philo)
	{
        pthread_mutex_destroy(&info->all_mutexes[i]);
        i++;
    }
}

int main(int argc, char *argv[])
{
    pthread_mutex_t *forks;
    pthread_t observer;
    pthread_t *philo_arr;
    t_info **info_arr;
    t_settings set;

    if (settings_init(&set, argc, argv))
	{
        return (1);
	}
	forks = create_fork(set);
    if (!forks)
		return (1);
    init_program(set, &philo_arr, &info_arr, forks);
    if (!philo_arr || !info_arr)
		return (1);
    pthread_create(&observer, NULL, &observer_routine, (void *)info_arr[0]);
    start_threads(philo_arr, info_arr, set);
    pthread_join(observer, NULL);
    join_all_threads(philo_arr, set);
    clean_mutexes(info_arr[0]);
    info_free_on_error(info_arr, set.number_of_philo);
	free(philo_arr);
    return (0);
}
