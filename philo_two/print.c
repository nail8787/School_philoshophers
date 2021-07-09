#include "philo_two.h"

void	print_philo_died(long now, t_philo philo, char *str, t_all_philo *all)
{
	sem_wait(all->print);
	printf("%ld ms %d %s\n", now, philo.phil_num, str);
}

void	print_philo(long now, t_philo *philo, char *str)
{
	sem_wait(philo->print);
	printf("%ld ms %d %s\n", now, philo->phil_num, str);
	sem_post(philo->print);
}

void	print_philo_forks(t_philo *philo)
{
	long	now;

	sem_wait(philo->print);
	now = get_now_time(philo);
	printf("%ld ms %d has taken fork\n", now, philo->phil_num);
	sem_post(philo->print);
}
