/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipaddr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 15:11:26 by dpowdere          #+#    #+#             */
/*   Updated: 2020/12/09 15:55:19 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ipaddr.h"

int	main(int argc, char **argv)
{
	t_cidr_ipv4	ip = { 0 };

	setlocale(LC_ALL, "");
	if (argc < 2 || argc > 3)
	{
		dprintf(STDERR, RED "Invalid number of arguments" RESET NL);
		dprintf(STDERR, SEEHELP);
		return (FAIL);
	}
	if (argc == 2 &&
			(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
	{
		printf(HELP);
		return (SUCCESS);
	}
	if (ft_recognize_cidr_ipv4(argc, argv, &ip) == NULL)
	{
		dprintf(STDERR, SEEHELP);
		return (FAIL);
	}
	ft_print_info(&ip);
	return (SUCCESS);
}

t_cidr_ipv4		*ft_recognize_cidr_ipv4(int argc, char **argv, t_cidr_ipv4 *ip)
{
	long int	n;
	char		*s;

	s = ft_recognize_ipv4(argv[1], &(ip->address));
	if (s == NULL)
	{
			dprintf(STDERR, RED "Invalid IPv4 Address or Netmask" RESET NL);
			return (NULL);
	}
	printf(NL "Trying to recognize arguments as ");
	if (argc == 3)
	{
		printf(UNDERLINE "IPv4 Address" RESET " "
				UNDERLINE "Netmask" RESET NL);
		if (*s == '/')
		{
			dprintf(STDERR, RED "Error: Both routing prefix length and netmask"
					" are indicated" RESET NL);
			return (NULL);
		}
		else if (*s)
		{
			dprintf(STDERR, RED "Invalid IPv4 Address" RESET NL);
			return (NULL);
		}
		s = ft_recognize_ipv4(argv[2], &(ip->mask));
		if (s == NULL || !ft_check_mask(ip->mask))
		{
			dprintf(STDERR, RED "Invalid Netmask" RESET NL);
			return (NULL);
		}
		ip->prefix_size = ft_mask_to_prefix_size(ip->mask);
	}
	else if (*s == '/')
	{
		printf(UNDERLINE "IPv4 Address" RESET "/"
				UNDERLINE "Routing prefix length" RESET NL);
		n = strtol(++s, NULL, BASE10);
		if (errno == ERANGE || n < 0 || n > 32)
		{
			dprintf(STDERR, RED "Invalid routing prefix length" RESET NL);
			return (NULL);
		}
		ip->prefix_size = (int)n;
		ip->mask = ft_prefix_size_to_mask(ip->prefix_size);
	}
	else
	{
		if (ft_check_mask(ip->address))
		{
			printf(UNDERLINE "Netmask" RESET " for zero IPv4 address" NL);
			ip->mask = ip->address;
			ip->prefix_size = ft_mask_to_prefix_size(ip->mask);
			ip->address.whole = (uint32_t)0;
		}
		else
		{
			printf(UNDERLINE "IPv4 Address" RESET " with zero netmask" NL);
			ip->mask.whole = (uint32_t)0;
			ip->prefix_size = 0;
		}
	}
	ft_populate_cidr_ipv4_struct(ip);
	return (ip);
}

char			*ft_recognize_ipv4(char *s, t_32bits *addr)
{
	char		*e;
	int			i;
	long int	n;

	i = 0;
	e = NULL;
	while (*s && i < 4)
	{
		if (*s == '.')
			++s;
		if (!isdigit(*s))
			return (NULL);
		n = strtol(s, &e, BASE10);
		if (errno == ERANGE || n < 0 || n > 255)
			return (NULL);
		addr->octets[i++] = (unsigned char)n;
		s = e;
	}
	while (*s && isspace(*s))
		++s;
	return (s);
}

int				ft_check_mask(t_32bits addr)
{
	int	i;
	int	j;
	int	is_prev0;
	int	bit;

	i = -1;
	is_prev0 = 0;
	while (++i < 4)
	{
		j = 8;
		while (--j >= 0)
		{
			bit = (addr.octets[i] >> j) & (unsigned char)1;
			if (is_prev0 && bit == 1)
				return (0);
			if (bit == 0)
				is_prev0 = 1;
		}
	}
	return (1);
}

int				ft_mask_to_prefix_size(t_32bits mask)
{
	int			i;
	int			j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 8)
			if (((mask.octets[i] >> (7 - j)) & (unsigned char)1)
					== (unsigned char)0)
				return (i * 8 + j);
	}
	return (32);
}

t_32bits		ft_prefix_size_to_mask(int prefix_size)
{
	int			i;
	int			diff;
	t_32bits	mask;

	i = 0;
	while (i < 4)
	{
		diff = (i + 1) * 8 - prefix_size;
		if (diff <= 0)
			mask.octets[i] = 0xff;
		else if (diff < 8)
			mask.octets[i] = 0xff << (8 - (prefix_size % 8));
		else
			mask.octets[i] = 0x0;
		++i;
	}
	return (mask);
}

void			ft_populate_cidr_ipv4_struct(t_cidr_ipv4 *ip)
{
	int			i;
	uint32_t	x;

	ip->postfix_size = 32 - ip->prefix_size;
	ip->network.whole = ip->address.whole & ip->mask.whole;
	ip->broadcast.whole = ip->network.whole | ~ip->mask.whole;
	ip->first_host_ip = ip->network;
	ip->first_host_ip.octets[3] |= (unsigned char)1;
	ip->last_host_ip = ip->broadcast;
	ip->last_host_ip.octets[3] &= ~(unsigned char)1;
	i = ip->postfix_size;
	x = 1;
	while (i-- > 0)
		x *= 2;
	ip->hosts = (x > 2 ? x - 2 : 0);
}

uint32_t		ft_big_to_little_endian(t_32bits big)
{
	uint32_t	n = 0;
	uint32_t	x;
	int			i;
	int			pow;

	i = 0;
	while (i < 4)
	{
		pow = 3 - i;
		x = 1;
		while (pow-- > 0)
			x *= 256;
		n += x * big.octets[i++];
	}
	return (n);
}

void			ft_print_info(t_cidr_ipv4 *ip)
{
	printf(NL);
	ft_print_section("CIDR IPv4 Address:");
	printf(BOLD GREEN);
	ft_print_decimal(ip->address);
	printf("/%d" RESET, ip->prefix_size);
	printf(NL);
	ft_print_section("Routing Prefix Length:");
	printf(GREEN "%d" RESET " bit(s)", ip->prefix_size);
	printf(NL);
	ft_print_section("Host Postfix Length:");
	printf(GREEN "%d" RESET " bit(s)", ip->postfix_size);
	printf(NL);
	ft_print_section("# Hosts in Subnet:");
	printf(GREEN "%'d" RESET " = 2^%d - 2", ip->hosts, ip->postfix_size);
	printf(NL);

	printf(NL UNDERLINE "Dot-decimal notation" RESET NL NL);

	ft_print_section("IPv4 Address:");
	printf(BLUE);
	ft_print_decimal(ip->address);
	printf(RESET NL);
	ft_print_section("Subnet Mask:");
	printf(BLUE);
	ft_print_decimal(ip->mask);
	printf(RESET NL);
	ft_print_section("Network Address:");
	printf(BLUE);
	ft_print_decimal(ip->network);
	printf(RESET NL);
	ft_print_section("Broadcast Address:");
	printf(BLUE);
	ft_print_decimal(ip->broadcast);
	printf(RESET NL);
	ft_print_section("Valid Host Addresses:");
	printf(BLUE);
	ft_print_decimal(ip->first_host_ip);
	printf("-");
	ft_print_decimal(ip->last_host_ip);
	printf(RESET NL);

	printf(NL UNDERLINE "Dot-binary notation" RESET NL NL);

	ft_print_section("IPv4 Address:");
	ft_print_binary(ip->address, ip->prefix_size);
	printf(NL);
	ft_print_section("Subnet Mask:");
	ft_print_binary(ip->mask, ip->prefix_size);
	printf(NL);
	ft_print_section("Network Address:");
	ft_print_binary(ip->network, ip->prefix_size);
	printf(NL);
	ft_print_section("Broadcast Address:");
	ft_print_binary(ip->broadcast, ip->prefix_size);
	printf(NL);
	ft_print_section("Valid Host Addresses");
	printf(NL);
	ft_print_section("from:");
	ft_print_binary(ip->first_host_ip, ip->prefix_size);
	printf(NL);
	ft_print_section("to:");
	ft_print_binary(ip->last_host_ip, ip->prefix_size);
	printf(NL NL);
}

void			ft_print_decimal(t_32bits addr)
{
	printf("%d", addr.octets[0]);
	for (int i = 1; i < 4; ++i)
		printf(".%d", addr.octets[i]);
}

void			ft_print_binary(t_32bits addr, int prefix_size)
{
	int i;
	int j;

	printf(COLOR);
	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 8; ++j)
		{
			if (i * 8 + j + 1 > prefix_size)
				printf(MAGENTA);
			if ((addr.octets[i] & ((unsigned char)1 << (7 - j))) > 0)
				printf("1");
			else
				printf("0");
		}
		if (i < 3)
			printf(".");
	}
	printf(RESET);
}
