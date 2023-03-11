/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_death.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:52:31 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/11 16:45:38 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meal(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->n_philo)
	{
		pthread_mutex_lock(&rules->philo[i].n_eat);
		if (rules->philo[i].nb_eat < rules->nb_eat)
		{
			pthread_mutex_unlock(&rules->philo[i].n_eat);	
			return (0);
		}
		pthread_mutex_unlock(&rules->philo[i].n_eat);
	}
	return (1);
}

void	*ft_death(void *args)
{
	t_rules *rules;
	t_philo *philo;
	int	i;
	int	j;

	rules = (t_rules *)args;
	while (1)
	{
		if (rules->nb_eat != -1 && check_meal(rules))
			break;
		i = -1;
		while (++i < rules->n_philo)
		{
			philo = &rules->philo[i];
			pthread_mutex_lock(&philo->l_eat);
			if (get_time() - philo->last_eat >= rules->t_death)
			{
				pthread_mutex_unlock(&philo->l_eat);
				pthread_mutex_lock(&rules->death);
				rules->death_flag = 1;
				pthread_mutex_unlock(&rules->death);
				j = -1;
				while (++j < rules->n_philo)
					pthread_detach(rules->philo[j].t_id);
				logs(&rules->philo[i], "died");
				return (NULL);
			}
			pthread_mutex_unlock(&philo->l_eat);
		}
		usleep(5000);
	}
	return (NULL);
}

// printf("PHILO :%d, TIME:%ld, LAST_EAT:%ld\n", rules->philo[i].id, get_time() - rules->start, rules->philo[i].last_eat);