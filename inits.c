/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csuomins <csuomins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:03:52 by csuomins          #+#    #+#             */
/*   Updated: 2026/02/01 13:51:50 by csuomins         ###   ########.fr       */
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
