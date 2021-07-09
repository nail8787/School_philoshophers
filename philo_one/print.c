#include "philo_one.h"

void	print_philo_died(long now, t_philo philo, char *str, t_all_philo *all)
{
	pthread_mutex_lock(all->print);
	printf("%ld ms %d %s\n", now, philo.phil_num, str);
}

void	print_philo(long now, t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->print);
	printf("%ld ms %d %s\n", now, philo->phil_num, str);
	pthread_mutex_unlock(philo->print);
}

void	print_philo_forks(long now, t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%ld ms %d has taken fork\n", now, philo->phil_num);
	pthread_mutex_unlock(philo->print);
}
