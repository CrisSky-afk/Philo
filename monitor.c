/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csuomins <csuomins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:04:11 by csuomins          #+#    #+#             */
/*   Updated: 2026/01/28 15:31:12 by csuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_all_finished(t_rules *r)
{
	int	all_finished;

	pthread_mutex_lock(&r->finish_mutex);
	if (r->must_eat != -1 && r->finished >= r->number_of_philosophers)
		all_finished = 1;
	else
		all_finished = 0;
	pthread_mutex_unlock(&r->finish_mutex);
	return (all_finished);
}

static int	check_philo_death(t_philo *p, t_rules *r, int i)
{
	long	time_since_meal;

	pthread_mutex_lock(&r->meal_mutex);
	time_since_meal = get_time() - p[i].last_meal;
	pthread_mutex_unlock(&r->meal_mutex);
	if (time_since_meal > r->time_to_die)
	{
		pthread_mutex_lock(&r->dead_mutex);
		r->dead = 1;
		pthread_mutex_unlock(&r->dead_mutex);
		pthread_mutex_lock(&r->print);
		printf("%ld %d died\n", get_time() - r->start_time, p[i].id);
		pthread_mutex_unlock(&r->print);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*p;
	t_rules	*r;
	int		i;

	p = (t_philo *)arg;
	r = p[0].rules;
	while (1)
	{
		if (check_all_finished(r))
			return (NULL);
		i = 0;
		while (i < r->number_of_philosophers)
		{
			if (check_philo_death(p, r, i))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
