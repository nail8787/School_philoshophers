#include "philo_two.h"

void	init_philo(t_philo *philo, int number_of_philo,
					char **argv, t_all_philo *all)
{
	philo->phil_num = number_of_philo;
	philo->forks = all->forks;
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

void	init_philo_threads(t_all_philo *all, char **argv)
{
	pthread_t	philo_thread[ft_atoi(argv[1])];
	int			i;

	i = 0;
	while (i < all->number_of_philos)
	{
		all->current_philo = i;
		pthread_create(&philo_thread[i], NULL, eat, &all->philo[i]);
		i++;
		usleep(50);
	}
	all->philo_thread = philo_thread;
}

int		init_sem_get_forks(t_all_philo *all)
{
	all->get_forks = sem_open("/get_forks", O_CREAT | O_EXCL,
		077, all->number_of_philos / 2);
	if (all->get_forks == SEM_FAILED)
	{
		if (errno == 17)
			sem_unlink("/get_forks");
		all->get_forks = sem_open("/get_forks", O_CREAT | O_EXCL,
			0777, all->number_of_philos / 2);
		if (all->get_forks == SEM_FAILED)
			return (-1);
	}
	return (0);
}

int		init_semaphore(t_all_philo *all)
{
	all->forks = sem_open("/philosophers", O_CREAT | O_EXCL, 0777,
		all->number_of_philos);
	if (all->forks == SEM_FAILED)
	{
		if (errno == 17)
			sem_unlink("/philosophers");
		all->forks = sem_open("/philosophers", O_CREAT | O_EXCL, 0777,
			all->number_of_philos);
		if (all->forks == SEM_FAILED)
			return (-1);
	}
	all->print = sem_open("/print", O_CREAT | O_EXCL, 077, 1);
	if (all->print == SEM_FAILED)
	{
		if (errno == 17)
			sem_unlink("/print");
		all->print = sem_open("/print", O_CREAT | O_EXCL, 0777, 1);
		if (all->print == SEM_FAILED)
			return (-1);
	}
	if (init_sem_get_forks(all) == -1)
		return (-1);
	return (0);
}
