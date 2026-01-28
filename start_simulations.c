#include "philo.h"

void	take_forks(t_philo *p)
{
	int	first;
	int	second;

	if (p->left < p->right)
	{
		first = p->left;
		second = p->right;
	}
	else
	{
		first = p->right;
		second = p->left;
	}
	pthread_mutex_lock(&p->rules->forks[first]);
	print_status(p, "has taken a fork");
	pthread_mutex_lock(&p->rules->forks[second]);
	print_status(p, "has taken a fork");
}

void	drop_forks(t_philo *p)
{
	pthread_mutex_unlock(&p->rules->forks[p->left]);
	pthread_mutex_unlock(&p->rules->forks[p->right]);
}

void	philo_eat(t_philo *p)
{
	if (p->rules->must_eat != -1 && p->meals >= p->rules->must_eat)
		return ;
	pthread_mutex_lock(&p->rules->meal_mutex);
	p->last_meal = get_time();
	pthread_mutex_unlock(&p->rules->meal_mutex);
	print_status(p, "is eating");
	ft_usleep(p->rules->time_to_eat);
	pthread_mutex_lock(&p->rules->meal_mutex);
	p->meals++;
	pthread_mutex_unlock(&p->rules->meal_mutex);
	if (p->rules->must_eat != -1 && p->meals == p->rules->must_eat)
	{
		pthread_mutex_lock(&p->rules->finish_mutex);
		p->rules->finished++;
		pthread_mutex_unlock(&p->rules->finish_mutex);
	}
}

void	philo_sleep(t_philo *p)
{
	print_status(p, "is sleeping");
	ft_usleep(p->rules->time_to_sleep);
}

void	philo_think(t_philo *p)
{
	print_status(p, "is thinking");
	usleep(500);
}
