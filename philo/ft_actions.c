/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 10:57:55 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/31 16:55:15 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_logs(t_philo *philo, char *message)
{
	long long	time;

	pthread_mutex_lock(&philo->rules->flag);
	if (philo->rules->stop_flag == 1 && message && message[0] != 'd')
	{
		pthread_mutex_unlock(&philo->rules->flag);
		return ;
	}
	time = get_time();
	pthread_mutex_lock(&philo->rules->logs);
	printf("%lld %d %s\n", time - philo->rules->start, philo->id, message);
	pthread_mutex_unlock(&philo->rules->logs);
	pthread_mutex_unlock(&philo->rules->flag);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->rules->forks[philo->r_fork]);
	else
		pthread_mutex_lock(&philo->rules->forks[philo->l_fork]);
	ft_logs(philo, "has taken a fork");
	if (philo->l_fork == philo->r_fork)
	{
		pthread_mutex_unlock(&philo->rules->forks[philo->r_fork]);
		return (1);
	}
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->rules->forks[philo->l_fork]);
	else
		pthread_mutex_lock(&philo->rules->forks[philo->r_fork]);
	ft_logs(philo, "has taken a fork");
	return (0);
}

void	release_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->rules->forks[philo->r_fork]);
		pthread_mutex_unlock(&philo->rules->forks[philo->l_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->rules->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->rules->forks[philo->r_fork]);
	}
}

int	ft_eat(t_philo *philo)
{
	if (take_forks(philo))
		return (1);
	ft_logs(philo, "is eating");
	pthread_mutex_lock(&philo->eat_info);
	philo->last_eat = get_time();
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->eat_info);
	ft_usleep(philo->rules->t_eat);
	release_forks(philo);
	return (0);
}
