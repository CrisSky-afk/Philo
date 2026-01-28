/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csuomins <csuomins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:04:18 by csuomins          #+#    #+#             */
/*   Updated: 2026/01/28 14:04:19 by csuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *p, char *msg)
{
	pthread_mutex_lock(&p->rules->dead_mutex);
	if (!p->rules->dead)
	{
		pthread_mutex_lock(&p->rules->print);
		printf("%ld %d %s\n",
			get_time() - p->rules->start_time, p->id, msg);
		pthread_mutex_unlock(&p->rules->print);
	}
	pthread_mutex_unlock(&p->rules->dead_mutex);
}

int	check_dead(t_philo *p)
{
	int	dead;

	pthread_mutex_lock(&p->rules->dead_mutex);
	dead = p->rules->dead;
	pthread_mutex_unlock(&p->rules->dead_mutex);
	return (dead);
}

int	check_finished(t_philo *p)
{
	int	finished;

	pthread_mutex_lock(&p->rules->finish_mutex);
	if (p->rules->must_eat != -1
		&& p->rules->finished >= p->rules->number_of_philosophers)
		finished = 1;
	else
		finished = 0;
	pthread_mutex_unlock(&p->rules->finish_mutex);
	return (finished);
}

static void	*single_philo(t_philo *p)
{
	pthread_mutex_lock(&p->rules->forks[p->left]);
	print_status(p, "has taken a fork");
	ft_usleep(p->rules->time_to_die);
	pthread_mutex_unlock(&p->rules->forks[p->left]);
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->rules->number_of_philosophers == 1)
		return (single_philo(p));
	if (p->id % 2 == 0)
		usleep(1000);
	while (!check_dead(p) && !check_finished(p))
	{
		take_forks(p);
		philo_eat(p);
		drop_forks(p);
		if (check_dead(p) || check_finished(p))
			break ;
		philo_sleep(p);
		philo_think(p);
	}
	return (NULL);
}
