#include "philo_one.h"

void	init_philo(t_philo *philo, int number_of_philo,
					char **argv, t_all_philo *all)
{
	philo->phil_num = number_of_philo;
	if (number_of_philo == 1)
	{
		philo->right_fork = all->forks[all->number_of_philos - 1];
		philo->left_fork = all->forks[0];
	}
	else
	{
		philo->right_fork = all->forks[number_of_philo - 2];
		philo->left_fork = all->forks[number_of_philo - 1];
	}
	philo->last_meal = 0;
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->eat_count = 0;
	philo->start = all->start;
	philo->times_to_eat = all->times_to_eat;
	philo->print = all->print;
}

int		init_philos(t_all_philo *all, char **argv)
{
	int	i;

	all->philo = (t_philo *)malloc(sizeof(t_philo) * all->number_of_philos);
	if (!all->philo)
		return (-1);
	i = 0;
	while (i < all->number_of_philos)
	{
		init_philo(&all->philo[i], i + 1, argv, all);
		i++;
	}
	return (0);
}

int		init_mutex(t_all_philo *all)
{
	int i;

	all->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!all->print)
		return (-1);
	pthread_mutex_init(all->print, NULL);
	all->forks = malloc(sizeof(pthread_mutex_t *)
		* (all->number_of_philos + 1));
	if (!all->forks)
		return (-1);
	all->forks[all->number_of_philos] = NULL;
	i = 0;
	while (i < all->number_of_philos)
	{
		all->forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!all->forks[i])
			return (-1);
		pthread_mutex_init(all->forks[i++], NULL);
	}
	return (0);
}

int		init_philo_threads(t_all_philo *all, char **argv)
{
	pthread_t	philo_thread[ft_atoi(argv[1])];
	int			i;

	i = 0;
	while (i < all->number_of_philos)
	{
		all->current_philo = i;
		if (pthread_create(&philo_thread[i], NULL, eat, &all->philo[i]) != 0)
			return (-1);
		i++;
		usleep(50);
	}
	all->philo_thread = philo_thread;
	return (0);
}
