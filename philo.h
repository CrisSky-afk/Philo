/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csuomins <csuomins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:04:24 by csuomins          #+#    #+#             */
/*   Updated: 2026/01/28 15:42:28 by csuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_rules
{
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat;

	long			start_time;
	int				dead;
	int				finished;

	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	finish_mutex;
	pthread_mutex_t	meal_mutex;
}	t_rules;

typedef struct s_philo
{
	int				id;
	int				meals;
	long			last_meal;
	int				left;
	int				right;
	pthread_t		thread;
	t_rules			*rules;
}	t_philo;

long	get_time(void);
void	ft_usleep(long time);
int		ft_atoi(const char *str);
int		ft_is_digit(char *str);

int		init_args(t_rules *r, int ac, char **av, t_philo **philos);

void	*philo_routine(void *arg);
void	*monitor_routine(void *arg);

void	take_forks(t_philo *p);
void	drop_forks(t_philo *p);
void	philo_eat(t_philo *p);
void	philo_sleep(t_philo *p);
void	philo_think(t_philo *p);

void	print_status(t_philo *p, char *msg);
int		check_dead(t_philo *p);
int		check_finished(t_philo *p);

void	cleanup(t_rules *r, t_philo *philos);

#endif