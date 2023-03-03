/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:02:21 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/03 17:54:33 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Create the thread (philo) and store the id
// prevent thread to take the same fork if a fork has been taken prevent with a mutex
// if fork unavailable -> wait for thread to finish else take the fork and eat
// store when a philo start eating
// check death : if a philo hasn't start to eat Xms since the beginning of his last meal -> death

// philo 1 will take his fork and the fork of NB_PHILO
// other will take his fork and the fork of cur_philo - 1

// ?? loop until a philo died create thread


// int create_thread(t_rules *rules)
// {
// 	int i;
// 	t_philo *philo;

// 	i = 0;
// 	philo = malloc(sizeof(t_philo) * rules->philo);
// 	while (i < rules->philo)
// 	{
// 		pthread_create(&philo[i].id, NULL, philo, rules);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < rules->philo)
// 	{
// 		pthread_join(philo[i].id, NULL);
// 		i++;
// 	}
// 	free(philo);
// 	return (0);
// }

int	main(int ac, char **av)
{
	t_rules rules;
	long long start;

	start = get_time();
	if (ac < 5)
		return(printf("Error expected at least 4 arguments"), 0);
	init_rules(&rules, ac, av);
	return (0);
}
