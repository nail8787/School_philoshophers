#include "philo_three.h"

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

int		eating(t_philo *philo)
{
	long	now;

	now = get_now_time(philo);
	print_philo(now, philo, "eating");
	philo->last_meal = get_now_time(philo);
	while (get_now_time(philo) <= now + philo->time_to_eat)
		usleep(50);
	philo->eat_count++;
	sem_post(philo->forks);
	sem_post(philo->forks);
	if (philo->eat_count == philo->times_to_eat)
	{
		philo->full = 1;
		return (1);
	}
	return (0);
}

void	*eat(void *args)
{
	t_philo		*philo;
	long		now;

	philo = (t_philo *)args;
	while (1)
	{
		sem_wait(philo->get_forks);
		sem_wait(philo->forks);
		now = get_now_time(philo);
		print_philo_forks(now, philo);
		sem_wait(philo->forks);
		sem_post(philo->get_forks);
		now = get_now_time(philo);
		print_philo_forks(now, philo);
		if (eating(philo) == 1)
			break ;
		now = get_now_time(philo);
		print_philo(now, philo, "sleeping");
		while (get_now_time(philo) <= now + philo->time_to_eat)
			usleep(10);
		now = get_now_time(philo);
		print_philo(now, philo, "thinking");
	}
	return ((void *)0);
}

int		main(int argc, char **argv)
{
	t_all_philo	all;
	int			i;

	if (argc != 5 && argc != 6)
		return (printf("Error: wrong number of arguments"));
	if (argc == 6)
		all.times_to_eat = ft_atoi(argv[5]);
	else
		all.times_to_eat = -1;
	all.number_of_philos = ft_atoi(argv[1]);
	if (init_semaphore(&all) == -1)
		return (printf("Error: sem_open failed"));
	i = 0;
	if (!(all.pids = malloc(sizeof(pid_t) * all.number_of_philos)))
		return (printf("Error: malloc failed"));
	gettimeofday(&all.start, NULL);
	init_philos(&all, argv);
	while (i < all.number_of_philos)
		init_process(&all, i++);
	wait_philo(&all);
	return (0);
}
