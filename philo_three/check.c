#include "philo_three.h"

void	check(t_philo *philo)
{
	long		now_time;

	while (1)
	{
		now_time = get_now_time(philo);
		if ((now_time - philo->last_meal) > philo->time_to_die)
		{
			print_philo_died(now_time, philo, "died");
			exit(2);
		}
		if (philo->full == 1)
			exit(0);
		usleep(50);
	}
}

void	kill_all(t_all_philo *all)
{
	int	i;

	i = 0;
	while (i < all->number_of_philos)
	{
		kill(all->pids[i], SIGTERM);
		i++;
	}
}

void	wait_philo(t_all_philo *all)
{
	int status;
	int	eat_count;

	eat_count = 0;
	while (eat_count < all->number_of_philos)
	{
		waitpid(0, &status, 0);
		if (WEXITSTATUS(status) == 0)
			eat_count++;
		if (WEXITSTATUS(status) == 2)
		{
			kill_all(all);
			exit(0);
		}
	}
	kill_all(all);
	exit(0);
}

void	close_philo(void)
{
	sem_unlink("/philosophers");
	sem_unlink("/print");
	sem_unlink("/get_forks");
}
