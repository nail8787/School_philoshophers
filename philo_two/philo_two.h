#ifndef PHILO_TWO_H
# define PHILO_TWO_H
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <errno.h>

typedef struct		s_philo {
	unsigned int	phil_num;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*get_forks;
	struct timeval	now;
	struct timeval	start;
	long			last_meal;
	long			start_meal;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				eat_count;
	int				times_to_eat;
}					t_philo;

typedef struct		s_all_philo {
	t_philo			*philo;
	pthread_t		*philo_thread;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*get_forks;
	struct timeval	now;
	struct timeval	start;
	long			now_time;
	int				philo_died;
	int				number_of_philos;
	int				times_to_eat;
	int				philos_full;
	int				current_philo;
}					t_all_philo;

void				*eat(void *args);
void				init_philo(t_philo *philo, int number_of_philo,
						char **argv, t_all_philo *all);
int					init_philos(t_all_philo *all, char **argv);
int					init_semaphore(t_all_philo *all);
void				init_philo_threads(t_all_philo *args, char **argv);
void				check(t_all_philo *args);
void				print_philo_died(long now, t_philo philo,
						char *str, t_all_philo *all);
void				print_philo(long now, t_philo *philo, char *str);
void				print_philo_forks(t_philo *philo);
int					ft_atoi(const char *str);
void				close_philo(void);
long				get_now_time(t_philo *philo);
long				get_now_time_death(t_all_philo *all);

#endif
