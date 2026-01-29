/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:03:52 by csuomins          #+#    #+#             */
/*   Updated: 2026/01/29 12:12:42 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_control_mutexes(t_rules *r)
{
	if (pthread_mutex_init(&r->print, NULL))
		return (1);
	if (pthread_mutex_init(&r->dead_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&r->finish_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&r->meal_mutex, NULL))
		return (1);
	return (0);
}

static int	init_fork_mutexes(t_rules *r)
{
	int	i;

	i = 0;
	while (i < r->number_of_philosophers)
	{
		if (pthread_mutex_init(&r->forks[i], NULL))
			return (1);
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

static int	validate_args(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (1);
	i = 1;
	while (i < ac)
	{
		if (!ft_is_digit(av[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	parse_arguments(t_rules *r, int ac, char **av)
{
	r->number_of_philosophers = ft_atoi(av[1]);
	r->time_to_die = ft_atoi(av[2]);
	r->time_to_eat = ft_atoi(av[3]);
	r->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		r->must_eat = ft_atoi(av[5]);
	else
		r->must_eat = -1;
	if (r->number_of_philosophers <= 0 || r->time_to_die <= 0)
		return (1);
	return (0);
}

static int	allocate_memory(t_rules *r, t_philo **philos)
{
	r->forks = malloc(sizeof(pthread_mutex_t) * r->number_of_philosophers);
	*philos = malloc(sizeof(t_philo) * r->number_of_philosophers);
	if (!r->forks || !*philos)
		return (1);
	return (0);
}

int	init_args(t_rules *r, int ac, char **av, t_philo **philos)
{
	if (validate_args(ac, av))
		return (1);
	if (parse_arguments(r, ac, av))
		return (1);
	r->dead = 0;
	r->finished = 0;
	r->start_time = get_time();
	if (allocate_memory(r, philos))
		return (1);
	if (init_control_mutexes(r))
		return (1);
	if (init_fork_mutexes(r))
		return (1);
	init_philos(r, *philos);
	return (0);
}
