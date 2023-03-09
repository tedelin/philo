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
		pthread_mutex_lock(&rules->forks[philo->r_fork]);
	else
		pthread_mutex_lock(&rules->forks[philo->l_fork]);
	logs(philo, "has taken a fork");
	if (philo->id == rules->n_philo)
		pthread_mutex_lock(&rules->forks[philo->l_fork]);
	else
		pthread_mutex_lock(&rules->forks[philo->r_fork]);
	logs(philo, "has taken a fork");
	logs(philo, "is eating");
	philo->nb_eat++;
	philo->last_eat = get_time();
	usleep(rules->t_eat * 1000);
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

void	init_philo(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->n_philo)
	{
		rules->philo[i].id = i + 1;
		rules->philo[i].rules = rules;
		rules->philo[i].l_fork = i;
		rules->philo[i].r_fork = (i + 1) % rules->n_philo;
	}
}

void	*ft_routine(void *args)
{
	t_philo	philo;
	t_rules	*rules;

	philo = *(t_philo *)args;
	rules = philo.rules;
	while (1)
	{
		eat(rules, &philo);
		if (rules->nb_eat != -1 && philo.nb_eat == rules->nb_eat)
			break ;
		usleep(200);
	}
	return (NULL);
}

void	create_thread(t_rules *rules)
{
	int		i;

	rules->philo = malloc(sizeof(t_philo) * rules->n_philo);
	memset(rules->philo, 0, sizeof(t_philo) * rules->n_philo); // check behavior
	init_philo(rules);
	i = -1;
	while (++i < rules->n_philo)
		pthread_create(&rules->philo[i].t_id, NULL, ft_routine, &rules->philo[i]);
	i = -1;
	while (++i < rules->n_philo)
		pthread_join(rules->philo[i].t_id, NULL);
	m_destroy(rules);
	free(rules->philo);
	free(rules->forks);
}
