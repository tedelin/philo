/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:59:11 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/08 18:13:18 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_rules *rules, t_philo *philo)
{
	if (philo->id == rules->n_philo)
		pthread_mutex_lock(philo->r_shield);
	else
		pthread_mutex_lock(&philo->l_shield);
	printf("%lld %d has taken a fork\n", get_time() - rules->start, philo->id);
	if (philo->id == rules->n_philo)
		pthread_mutex_lock(&philo->l_shield);
	else
		pthread_mutex_lock(philo->r_shield);
	printf("%lld %d has taken a fork\n", get_time() - rules->start, philo->id);
	printf("%lld %d is eating\n", get_time() - rules->start, philo->id);
	usleep(rules->t_eat * 1000);
	// if (philo->id == rules->n_philo)
	// {
	// 	pthread_mutex_unlock(philo->r_shield);
	// 	pthread_mutex_unlock(&philo->l_shield);
	// }
	// else
	// {
	// 	pthread_mutex_unlock(&philo->l_shield);
	// 	pthread_mutex_unlock(philo->r_shield);
	// }
}

void	init_philo(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->n_philo)
		pthread_mutex_init(&rules->philo[i].l_shield, NULL);
	// pthread_mutex_lock(&rules->philo[0].l_shield);
	i = -1;
	while (++i < rules->n_philo)
	{
		rules->philo[i].id = i + 1;
		if (i == rules->n_philo - 1)
		{
			rules->philo[i].r_shield = &(rules->philo[0].l_shield);
			rules->philo[i].r_fork = &(rules->philo[0].l_fork);
		}
		else
		{
			rules->philo[i].r_shield = &(rules->philo[i + 1].l_shield);
			rules->philo[i].r_fork = &(rules->philo[i + 1].l_fork);
		}
		rules->philo[i].rules = rules;	
		// pthread_mutex_init(&rules->philo[i].l_shield, NULL);
	}
}

void	*ft_routine(void *args)
{
	t_philo	philo;
	t_rules	*rules;

	philo = *(t_philo *)args;
	rules = philo.rules;
	int	i = -1;
	while (++i < 3)
	{
		eat(rules, &philo);
		usleep(200);
	}
	return (NULL);
}

void	create_thread(t_rules *rules)
{
	int		i;

	rules->philo = malloc(sizeof(t_philo) * rules->n_philo);
	memset(rules->philo, 0, sizeof(t_philo) * rules->n_philo);
	init_philo(rules);
	i = -1;
	while (++i < rules->n_philo)
	{
		pthread_create(&rules->philo[i].t_id, NULL, ft_routine, &rules->philo[i]);
	}
	i = -1;
	while (++i < rules->n_philo)
		pthread_join(rules->philo[i].t_id, NULL);
	m_destroy(rules);
	free(rules->philo);
}
