#include "philo.h"

static int	init_mutexes(t_rules *r)
{
	int	i;

	if (pthread_mutex_init(&r->print, NULL))
		return (1);
	if (pthread_mutex_init(&r->dead_mutex, NULL))
	{
		pthread_mutex_destroy(&r->print);
		return (1);
	}
	if (pthread_mutex_init(&r->finish_mutex, NULL))
	{
		pthread_mutex_destroy(&r->print);
		pthread_mutex_destroy(&r->dead_mutex);
		return (1);
	}
	if (pthread_mutex_init(&r->meal_mutex, NULL))
	{
		pthread_mutex_destroy(&r->print);
		pthread_mutex_destroy(&r->dead_mutex);
		pthread_mutex_destroy(&r->finish_mutex);
		return (1);
	}
	i = 0;
	while (i < r->number_of_philosophers)
	{
		if (pthread_mutex_init(&r->forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&r->forks[i]);
			pthread_mutex_destroy(&r->print);
			pthread_mutex_destroy(&r->dead_mutex);
			pthread_mutex_destroy(&r->finish_mutex);
			pthread_mutex_destroy(&r->meal_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	init_philos(t_rules *r, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < r->number_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].meals = 0;
		philos[i].last_meal = r->start_time;
		philos[i].left = i;
		philos[i].right = (i + 1) % r->number_of_philosophers;
		philos[i].rules = r;
		i++;
	}
}

int	init_args(t_rules *r, int ac, char **av, t_philo **philos)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (1);
	i = 1;
	while (i < ac)
	{
		if (!ft_is_digit(av[i]) || ft_atoi(av[i]) <= 0)
			return (1);
		i++;
	}
	r->number_of_philosophers = ft_atoi(av[1]);
	r->time_to_die = ft_atoi(av[2]);
	r->time_to_eat = ft_atoi(av[3]);
	r->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		r->must_eat = ft_atoi(av[5]);
	else
		r->must_eat = -1;
	r->dead = 0;
	r->finished = 0;
	r->start_time = get_time();
	r->forks = malloc(sizeof(pthread_mutex_t) * r->number_of_philosophers);
	*philos = malloc(sizeof(t_philo) * r->number_of_philosophers);
	if (!r->forks || !*philos)
		return (1);
	if (init_mutexes(r))
		return (1);
	init_philos(r, *philos);
	return (0);
}
