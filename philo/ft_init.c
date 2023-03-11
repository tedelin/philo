/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:09:27 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/10 17:26:59 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_rules(t_rules *rules, int ac, char **av)
{
	int	i;

	i = -1;
	memset(rules, 0, sizeof(t_rules));
	rules->t_death = ft_atol(av[2]);
	rules->t_eat = ft_atol(av[3]);
	rules->t_sleep = ft_atol(av[4]);
	rules->n_philo = ft_atol(av[1]);
	pthread_mutex_init(&rules->info, NULL);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->n_philo);
	if (!rules->forks)
		return ; // add protection
	while (++i < rules->n_philo)
		pthread_mutex_init(&rules->forks[i], NULL);
	if (ac == 6)
		rules->nb_eat = ft_atol(av[5]);
	else
		rules->nb_eat = -1;
	rules->start = get_time();
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
		rules->philo[i].last_eat = rules->start;
		rules->philo[i].r_fork = (i + 1) % rules->n_philo;
		pthread_mutex_init(&rules->philo[i].n_eat, NULL);
		pthread_mutex_init(&rules->philo[i].death, NULL);
		pthread_mutex_init(&rules->philo[i].l_eat, NULL);
	}
}

void	ft_usleep(long long time)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}
