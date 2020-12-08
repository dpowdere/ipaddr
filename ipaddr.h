/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipaddr.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 15:14:27 by dpowdere          #+#    #+#             */
/*   Updated: 2020/12/08 16:00:35 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IPADDR_H
# define IPADDR_H

# define SUCCESS	0
# define FAIL		1

# define BOLD	"\033[1m"
# define RESET	"\033[0m"
# define UNDERLINE	"\033[4m"

# define HELP	(\
	BOLD "NAME\n" RESET \
	"\tipaddr - show information about IPv4 addresses\n\n" \
	BOLD "SYNOPSYS:\n" RESET \
	"\tipaddr " UNDERLINE "IPv4 ADDRESS" RESET "/" \
				UNDERLINE "IPv4 ROUTING PREFIX LENGTH\n\n" \
	)

#endif
