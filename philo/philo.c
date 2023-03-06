/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:02:21 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/06 16:37:42 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_rules rules;

	if (ac < 5)
		return(printf("Error expected at least 4 arguments\n"), 0);
	init_rules(&rules, ac, av);
	create_thread(&rules);
	return (0);
}
