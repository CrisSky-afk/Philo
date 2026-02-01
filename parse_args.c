/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csuomins <csuomins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 13:46:50 by csuomins          #+#    #+#             */
/*   Updated: 2026/02/01 13:51:53 by csuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
