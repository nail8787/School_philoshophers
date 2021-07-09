#include "philo_three.h"

void	print_philo_died(long now, t_philo *philo, char *str)
{
	sem_wait(philo->print);
	printf("%ld ms %d %s\n", now, philo->phil_num, str);
}

void	print_philo(long now, t_philo *philo, char *str)
{
	sem_wait(philo->print);
	printf("%ld ms %d %s\n", now, philo->phil_num, str);
	sem_post(philo->print);
}

void	print_philo_forks(long now, t_philo *philo)
{
	sem_wait(philo->print);
	printf("%ld ms %d has taken fork\n", now, philo->phil_num);
	sem_post(philo->print);
}
