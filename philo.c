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
	int 			i;

    info_arr = malloc(sizeof(t_info *) * (set.number_of_philo + 1));
    if (!info_arr) 
		return (NULL);
    printf_lock = malloc(sizeof(pthread_mutex_t));
    if (!printf_lock)
		return (NULL);
    pthread_mutex_init(printf_lock, NULL);
	i = 0;
    while (i < set.number_of_philo)
	{
        info_arr[i] = malloc(sizeof(t_info));
        if (!info_arr[i])
            return (info_free_on_error(info_arr, i), free(printf_lock), NULL);
        init_info_arr_elems(info_arr[i], set, i, m);
        info_arr[i]->printf_lock = printf_lock;
        i++;
    }
    return (info_arr[i] = NULL, info_arr);
}

void    add_more_variable_to_info(t_info ***info_arr)
{
	pthread_mutex_t	*died_counter;
    pthread_mutex_t	*counter_lock;
    int				i;

	counter_lock = malloc(sizeof(pthread_mutex_t));
	if (!counter_lock)
		return (info_free_on_error(*info_arr, (*info_arr)[0]->set.number_of_philo));
	pthread_mutex_init(counter_lock, NULL);
    i = 0;
    while (i < (*info_arr)[0]->set.number_of_philo)
		(*info_arr)[i++]->counter_lock = counter_lock;
	died_counter = malloc(sizeof(pthread_mutex_t));
	if (!died_counter)
		return (info_free_on_error(*info_arr, (*info_arr)[0]->set.number_of_philo));
	pthread_mutex_init(died_counter, NULL);
	i = 0;
	while (i < (*info_arr)[0]->set.number_of_philo)
		(*info_arr)[i++]->died_counter = died_counter;
}

void	init_program(t_settings set, pthread_t **philo_arr, t_info ***info_arr, pthread_mutex_t *m)
{
    int *count_of_complete;
    int *is_any_died;
    int i;

    *info_arr = init_info_arr(set, m);
    if (!*info_arr)
        return ;
    is_any_died = malloc(sizeof(int));
    if (!is_any_died)
        return (info_free_on_error(*info_arr, set.number_of_philo));
    *is_any_died = 0;
    count_of_complete = malloc(sizeof(int));
    if (!count_of_complete)
        return (info_free_on_error(*info_arr, set.number_of_philo));
    *count_of_complete = 0;
    i = 0;
    while (i < (*info_arr)[0]->set.number_of_philo)
        (*info_arr)[i++]->is_any_died = is_any_died;
    i = 0;
    while (i < (*info_arr)[0]->set.number_of_philo)
        (*info_arr)[i++]->count_of_complete = count_of_complete;
    *philo_arr = malloc(sizeof(pthread_t) * set.number_of_philo);
    if (!*philo_arr)
        return info_free_on_error(*info_arr, set.number_of_philo);
    add_more_variable_to_info(info_arr);
}

void start_threads(pthread_t *philo_arr, t_info **info_arr, t_settings set)
{
    int i = 0;
    while (i < set.number_of_philo)
	{
        if (pthread_create(&philo_arr[i], NULL, &routine, (void *)info_arr[i]) != 0)
		{
			while (0 <= i)
			{
				pthread_join(philo_arr[i], NULL);
				i--;
			}
			break;
		}
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

int main(int argc, char *argv[])
{
    pthread_mutex_t *forks;
    pthread_t *philo_arr;
    t_info **info_arr;
    t_settings set;

	philo_arr = NULL;
	info_arr = NULL;
    if (settings_init(&set, argc, argv))
	{
        return (1);
	}
	forks = create_fork(set);
    if (!forks)
		return (1);
    init_program(set, &philo_arr, &info_arr, forks);
    if (!philo_arr || !info_arr)
		return (info_free_on_error(info_arr, set.number_of_philo), free_forks(forks), 1);
    start_threads(philo_arr, info_arr, set);
    join_all_threads(philo_arr, set);
    info_free_on_error(info_arr, set.number_of_philo);
	free(philo_arr);
    return (0);
}
