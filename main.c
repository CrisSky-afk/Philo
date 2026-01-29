/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:04:00 by csuomins          #+#    #+#             */
/*   Updated: 2026/01/29 12:12:22 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_rules *r, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < r->number_of_philosophers)
	{
		pthread_mutex_destroy(&r->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&r->print);
	pthread_mutex_destroy(&r->dead_mutex);
	pthread_mutex_destroy(&r->finish_mutex);
	pthread_mutex_destroy(&r->meal_mutex);
	free(r->forks);
	free(philos);
}

static void	create_threads(t_rules *rules, t_philo *philos, pthread_t *monitor)
{
	int	i;

	pthread_create(monitor, NULL, monitor_routine, philos);
	i = 0;
	while (i < rules->number_of_philosophers)
	{
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
		i++;
	}
}

static void	join_threads(t_rules *rules, t_philo *philos, pthread_t monitor)
{
	int	i;

	pthread_join(monitor, NULL);
	i = 0;
	while (i < rules->number_of_philosophers)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_rules		rules;
	t_philo		*philos;
	pthread_t	monitor;

	if (init_args(&rules, ac, av, &philos))
	{
		printf("Error\n");
		return (1);
	}
	create_threads(&rules, philos, &monitor);
	join_threads(&rules, philos, monitor);
	cleanup(&rules, philos);
	return (0);
}
