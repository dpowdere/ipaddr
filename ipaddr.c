/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipaddr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 15:11:26 by dpowdere          #+#    #+#             */
/*   Updated: 2020/12/08 15:16:49 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ipaddr.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf(HELP);
		return (FAIL);
	}
	(void)argv;
}
