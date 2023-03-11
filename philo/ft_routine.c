/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:59:11 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/11 16:38:52 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_rules *rules, t_philo *philo)
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
	pthread_mutex_lock(&philo->n_eat);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->n_eat);
	pthread_mutex_lock(&philo->l_eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->l_eat);
	ft_usleep(rules->t_eat);
	if (philo->id == rules->n_philo)
	{
		pthread_mutex_unlock(&rules->forks[philo->r_fork]);
		pthread_mutex_unlock(&rules->forks[philo->l_fork]);
		return ;
	}
	pthread_mutex_unlock(&rules->forks[philo->l_fork]);
	pthread_mutex_unlock(&rules->forks[philo->r_fork]);
}

void	*ft_routine(void *args)
{
	t_philo	philo;
	t_rules	*rules;

	philo = *(t_philo *)args;
	rules = philo.rules;
	while (1)
	{
		ft_eat(rules, &philo);
		if (rules->nb_eat != -1 && philo.nb_eat == rules->nb_eat)
			break ;
		logs(&philo, "is sleeping");
		ft_usleep(rules->t_sleep);
		logs(&philo, "is thinking");
		pthread_mutex_lock(&rules->death);
		if (rules->death_flag == 1)
		{
			pthread_mutex_unlock(&rules->death);
			break ;
		}
		pthread_mutex_unlock(&rules->death);
	}
	return (NULL);
}

void	create_thread(t_rules *rules)
{
	pthread_t id_err;
	int		i;

	rules->philo = malloc(sizeof(t_philo) * rules->n_philo);
	memset(rules->philo, 0, sizeof(t_philo) * rules->n_philo); // check behavior
	init_philo(rules);
	i = -1;
	while (++i < rules->n_philo)
		pthread_create(&rules->philo[i].t_id, NULL, ft_routine, &rules->philo[i]);
	pthread_create(&id_err, NULL, ft_death, rules);
	i = -1;
	while (++i < rules->n_philo)
		pthread_join(rules->philo[i].t_id, NULL);
	pthread_join(id_err, NULL);
	ft_free(rules);
}
