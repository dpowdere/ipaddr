/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipaddr.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 15:14:27 by dpowdere          #+#    #+#             */
/*   Updated: 2020/12/09 15:55:22 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IPADDR_H
# define IPADDR_H

# include <ctype.h>
# include <errno.h>
# include <locale.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define BASE10	10

# define SUCCESS	0
# define FAIL		1

# define STDERR	2

# define NL		"\n"
# define TAB	"\t"

# define BLUE		"\033[34m"
# define BOLD		"\033[1m"
# define COLOR		BLUE
# define GREEN		"\033[32m"
# define MAGENTA	"\033[35m"
# define RED		"\033[31m"
# define RESET		"\033[0m"
# define UNDERLINE	"\033[4m"
# define YELLOW		"\033[33m"

# define SEEHELP	( \
		NL "See program's help using " UNDERLINE "-h" RESET " or " \
		UNDERLINE "--help" RESET " argument" NL NL)

# define HELP	( \
	NL \
	BOLD "NAME" RESET NL \
	TAB "ipaddr - show information about IPv4 addresses" NL \
	NL \
	BOLD "SYNOPSYS:" RESET NL \
	TAB "ipaddr " UNDERLINE "IPv4 ADDRESS" RESET "/" \
				UNDERLINE "ROUTING PREFIX LENGTH" RESET NL \
	TAB "ipaddr " UNDERLINE "IPv4 ADDRESS" RESET " " \
				UNDERLINE "NETMASK" RESET NL \
	TAB "ipaddr " UNDERLINE "IPv4 ADDRESS" RESET NL \
	TAB "ipaddr " UNDERLINE "NETMASK" RESET NL \
	NL \
	)

# define SPECIAL_USE_ADDRESSES	( \
	UNDERLINE "Special Use IPv4 Addresses (RFC 6890)" \
	)

typedef union	u_32bits
{
	uint32_t		whole;
	unsigned char	octets[4];
}				t_32bits;

typedef struct	s_cidr_ipv4
{
	t_32bits	address;
	t_32bits	mask;
	int			prefix_size;
	int			postfix_size;

	t_32bits	network;
	t_32bits	broadcast;

	t_32bits	first_host_ip;
	t_32bits	last_host_ip;

	uint32_t	hosts;
}				t_cidr_ipv4;

extern int		errno;

t_cidr_ipv4		*ft_recognize_cidr_ipv4(int argc, char **argv, t_cidr_ipv4 *ip);
char			*ft_recognize_ipv4(char *s, t_32bits *addr);
uint32_t		ft_big_to_little_endian(t_32bits big);
int				ft_check_mask(t_32bits addr);
void			ft_populate_cidr_ipv4_struct(t_cidr_ipv4 *ip);
void			ft_print_binary(t_32bits addr, int prefix_size);
void			ft_print_decimal(t_32bits addr);
void			ft_print_info(t_cidr_ipv4 *ip);

int				ft_mask_to_prefix_size(t_32bits mask);
t_32bits		ft_prefix_size_to_mask(int prefix_size);

# define ft_print_section(x)	printf("%24s ", x);

#endif
