#include "philo_two.h"

int		check_death(t_all_philo *args)
{
	long	now_time;
	int		i;

	i = 0;
	while (i < args->number_of_philos)
	{
		now_time = get_now_time_death(args);
		if (args->philo[i].eat_count == args->times_to_eat)
		{
			i++;
			continue ;
		}
		if ((now_time - args->philo[i].last_meal) >=
			args->philo[i].time_to_die)
		{
			print_philo_died(now_time, args->philo[i], "died", args);
			return (1);
		}
		i++;
		usleep(50);
	}
	return (0);
}

int		check_full(t_all_philo *args)
{
	int	i;
	int	full_count;

	i = 0;
	full_count = 0;
	while (i < args->number_of_philos)
	{
		if (args->philo[i++].eat_count == args->times_to_eat)
			full_count++;
		else
			break ;
	}
	if (full_count == args->number_of_philos)
		return (1);
	return (0);
}

void	check(t_all_philo *args)
{
	while (1)
	{
		if (check_death(args) == 1)
			break ;
		if (check_full(args) == 1)
			break ;
	}
}

void	close_philo(void)
{
	sem_unlink("/philosophers");
	sem_unlink("/print");
	sem_unlink("/get_forks");
}
