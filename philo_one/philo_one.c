#include "philo_one.h"

long	get_now_time_death(t_all_philo *all)
{
	struct timeval	now;
	long			now_time;

	gettimeofday(&now, NULL);
	now_time = (now.tv_sec * 1000 + now.tv_usec / 1000) -
		(all->start.tv_sec * 1000 +
			all->start.tv_usec / 1000);
	return (now_time);
}

long	get_now_time(t_philo *philo)
{
	struct timeval	now;
	long			now_time;

	gettimeofday(&now, NULL);
	now_time = (now.tv_sec * 1000 + now.tv_usec / 1000) -
		(philo->start.tv_sec * 1000 +
			philo->start.tv_usec / 1000);
	return (now_time);
}

void	eating(t_philo *philo)
{
	long	now;

	now = get_now_time(philo);
	print_philo(now, philo, "eating");
	philo->last_meal = get_now_time(philo);
	while (get_now_time(philo) <= now + philo->time_to_eat)
		usleep(100);
	philo->eat_count++;
}

void	*eat(void *args)
{
	t_philo		*philo;
	long		now;

	philo = (t_philo *)args;
	while (1)
	{
		pthread_mutex_lock(philo->right_fork);
		now = get_now_time(philo);
		print_philo_forks(now, philo);
		pthread_mutex_lock(philo->left_fork);
		now = get_now_time(philo);
		print_philo_forks(now, philo);
		eating(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (philo->eat_count == philo->times_to_eat)
			break ;
		now = get_now_time(philo);
		print_philo(now, philo, "sleeping");
		while (get_now_time(philo) <= now + philo->time_to_eat)
			usleep(100);
		now = get_now_time(philo);
		print_philo(now, philo, "thinking");
	}
	return ((void *)0);
}

int		main(int argc, char **argv)
{
	t_all_philo	all;

	if (argc != 5 && argc != 6)
		return (printf("Error: wrong number of arguments\n"));
	if (argc == 6)
		all.times_to_eat = ft_atoi(argv[5]);
	else
		all.times_to_eat = -1;
	all.number_of_philos = ft_atoi(argv[1]);
	if (init_mutex(&all) == -1)
		return (printf("Error: malloc failed\n"));
	gettimeofday(&all.start, NULL);
	if (init_philos(&all, argv) == -1)
		return (printf("Error: malloc failed\n"));
	if (init_philo_threads(&all, argv) == -1)
		return (printf("Error: pthread_create failed\n"));
	check(&all);
	return (0);
}
