/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:02:21 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/12 11:07:39 by tedelin          ###   ########.fr       */
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
	pthread_mutex_init(&rules->death, NULL);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->n_philo);
	if (!rules->forks)
		return ;
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
		pthread_mutex_init(&rules->philo[i].l_eat, NULL);
	}
}

int	main(int ac, char **av)
{
	t_rules	rules;

	if (!ft_args(ac, av))
		return (printf("Error ARGS\n"), 0);
	if (ac < 5)
		return (printf("Error expected at least 4 arguments\n"), 0);
	init_rules(&rules, ac, av);
	ft_thread(&rules);
	return (0);
}
