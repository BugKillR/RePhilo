#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define INT_MAX	2147483647
# define INT_MIN	-2147483648

typedef struct s_settings
{
	long			number_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_eat_count;
	struct timeval	start_time;
}				t_settings;

typedef struct s_info
{
	pthread_mutex_t	*printf_lock;
	pthread_mutex_t	*counter_lock;
	pthread_mutex_t	*died_counter;
	pthread_mutex_t	*all_mutexes;
	t_settings		set;
	int				index_of_philo;
	int				*is_any_died;
	int				*count_of_complete;
}				t_info;

//	----- Initializers -----

int		settings_init(t_settings *set, int argc, char *argv[]);

//	----- Routines -----

void	*routine(void *arg);

long	ft_atol(const char *num);

//	----- STDOUT Functions -----

void	fork_message(long ms_passed, int philo_id, t_info info);
void	eat_message(long ms_passed, int philo_id, t_info info);
void	sleep_message(long ms_passed, int philo_id, t_info info);
void	think_message(long ms_passed, int philo_id, t_info info);
void	died_message(long ms_passed, int philo_id, t_info info);

//	----- Free Functions -----

void	info_free_on_error(t_info **info_arr, int count);
void	free_forks(pthread_mutex_t *forks);

#endif
