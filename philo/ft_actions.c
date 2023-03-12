/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 10:57:55 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/12 11:04:18 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	logs(t_philo *philo, char *message)
{
	long	time;

	pthread_mutex_lock(&philo->rules->death);
	if (philo->rules->death_flag == 1 && strcmp(message, "died") != 0)
	{
		pthread_mutex_unlock(&philo->rules->death);
		return ;
	}
	pthread_mutex_unlock(&philo->rules->death);
	time = get_time();
	pthread_mutex_lock(&philo->rules->info);
	printf("%ld %d %s\n", time - philo->rules->start, philo->id, message);
	pthread_mutex_unlock(&philo->rules->info);
}

void	take_forks(t_rules *rules, t_philo *philo)
{
	if (philo->id == rules->n_philo)
		pthread_mutex_lock(&rules->forks[philo->r_fork]);
	else
		pthread_mutex_lock(&rules->forks[philo->l_fork]);
	logs(philo, "has taken a fork");
	if (philo->id == rules->n_philo)
		pthread_mutex_lock(&rules->forks[philo->l_fork]);
	else
		pthread_mutex_lock(&rules->forks[philo->r_fork]);
	logs(philo, "has taken a fork");
}

void	release_forks(t_rules *rules, t_philo *philo)
{
	if (philo->id == rules->n_philo)
	{
		pthread_mutex_unlock(&rules->forks[philo->r_fork]);
		pthread_mutex_unlock(&rules->forks[philo->l_fork]);
	}
	else
	{
		pthread_mutex_unlock(&rules->forks[philo->l_fork]);
		pthread_mutex_unlock(&rules->forks[philo->r_fork]);
	}
}

void	ft_eat(t_rules *rules, t_philo *philo)
{
	take_forks(rules, philo);
	logs(philo, "is eating");
	pthread_mutex_lock(&philo->n_eat);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->n_eat);
	pthread_mutex_lock(&philo->l_eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->l_eat);
	ft_usleep(rules->t_eat);
	release_forks(rules, philo);
}
