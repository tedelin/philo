/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:59:11 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/06 17:07:30 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork);
		printf("%lld %d has taken a fork\n", get_time() - philo->rules.start, philo->id);
		pthread_mutex_lock(&philo->next->fork);
		printf("%lld %d has taken a fork\n", get_time() - philo->rules.start, philo->id);
		philo->last_eat = get_time() - philo->rules.start;
		printf("%lld %d is eating\n", philo->last_eat, philo->id);
		usleep(philo->rules.t_eat * 1000);
		pthread_mutex_unlock(&philo->next->fork);
		pthread_mutex_unlock(&philo->fork);
	}
	else
	{
		pthread_mutex_lock(&philo->next->fork);
		printf("%lld %d has taken a fork\n", get_time() - philo->rules.start, philo->id);
		pthread_mutex_lock(&philo->fork);
		printf("%lld %d has taken a fork\n", get_time() - philo->rules.start, philo->id);
		philo->last_eat = get_time() - philo->rules.start;
		printf("%lld %d is eating\n", philo->last_eat, philo->id);
		usleep(philo->rules.t_eat * 1000);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
	}
}

void	*ft_routine(void *args)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)args;
	i = -1;
	while (++i < 3)
	{
		eat(philo);
		printf("%lld %d is sleeping\n", get_time() - philo->rules.start, philo->id);
		usleep(philo->rules.t_sleep * 1000);
	}
	return (NULL);
}

void	create_thread(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = malloc(sizeof(t_philo) * rules->philo);
	memset(philo, 0, sizeof(t_philo) * rules->philo);
	while (++i < rules->philo)
	{
		philo[i].id = i + 1;
		ft_memcpy(&philo[i].rules, rules, sizeof(t_rules));
		if (i < rules->philo - 1)
			philo[i].next = &philo[i + 1];
		else
			philo[i].next = &philo[0];
		pthread_mutex_init(&philo[i].fork, NULL);
	}
	i = -1;
	while (++i < rules->philo)
		pthread_create(&philo[i].t_id, NULL, ft_routine, &philo[i]);
	i = -1;
	while (++i < rules->philo)
		pthread_join(philo[i].t_id, NULL);
	free(philo);
}
