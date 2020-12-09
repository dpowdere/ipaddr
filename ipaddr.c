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
	if (argc != 2)
	{
		printf(HELP);
		return (FAIL);
	}
	if (ft_recognize_cidr_ipv4(argv[1], &ip) == NULL)
	{
		printf(HELP);
		return (FAIL);
	}
	ft_print_info(&ip);
	return (SUCCESS);
}

t_cidr_ipv4		*ft_recognize_cidr_ipv4(char *s, t_cidr_ipv4 *ip)
{
	int			i = 0;
	char		*e = NULL;
	long int	n;

	while (*s && i < 4)
	{
		if (*s == '.')
			++s;
		n = strtol(s, &e, BASE10);
		if (errno == ERANGE || n < 0 || n > 255)
			return (NULL);
		ip->address.octets[i++] = (unsigned char)n;
		s = e;
	}
	if (*s == '/')
		++s;
	else
		return (NULL);
	n = strtol(s, &e, BASE10);
	if (errno == ERANGE || n < 0 || n > 32)
		return (NULL);
	ip->mask_size = (int)n;
	ft_populate_cidr_ipv4_struct(ip);
	return (ip);
}

void			ft_populate_cidr_ipv4_struct(t_cidr_ipv4 *ip)
{
	int			i;
	int			diff;
	uint32_t	x;

	i = 0;
	while (i < 4)
	{
		diff = (i + 1) * 8 - ip->mask_size;
		if (diff <= 0)
			ip->mask.octets[i] = 0xff;
		else if (diff < 8)
			ip->mask.octets[i] = 0xff << (8 - (ip->mask_size % 8));
		else
			ip->mask.octets[i] = 0x0;
		++i;
	}
	ip->network.whole = ip->address.whole & ip->mask.whole;
	ip->broadcast.whole = ip->network.whole | ~ip->mask.whole;
	ip->first_host_ip = ip->network;
	ip->first_host_ip.octets[3] |= (unsigned char)1;
	ip->last_host_ip = ip->broadcast;
	ip->last_host_ip.octets[3] &= ~(unsigned char)1;
	i = 32 - ip->mask_size;
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
	printf("/%d" RESET, ip->mask_size);
	printf(NL);
	ft_print_section("Routing Prefix Length:");
	printf(GREEN "%d" RESET " bit(s)", ip->mask_size);
	printf(NL);
	ft_print_section("Host Postfix Length:");
	printf(GREEN "%d" RESET " bit(s)", 32 - ip->mask_size);
	printf(NL);
	ft_print_section("# Hosts in Subnet:");
	printf(GREEN "%'d" RESET " = 2^%d - 2", ip->hosts, 32 - ip->mask_size);
	printf(NL);

	printf(NL UNDERLINE "Dot-decimal notation" RESET NL NL);

#	undef COLOR
#	define COLOR	BLUE
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
	ft_print_binary(ip->address, ip->mask_size);
	printf(NL);
	ft_print_section("Subnet Mask:");
	ft_print_binary(ip->mask, ip->mask_size);
	printf(NL);
	ft_print_section("Network Address:");
	ft_print_binary(ip->network, ip->mask_size);
	printf(NL);
	ft_print_section("Broadcast Address:");
	ft_print_binary(ip->broadcast, ip->mask_size);
	printf(NL);
	ft_print_section("Valid Host Addresses");
	printf(NL);
	ft_print_section("from:");
	ft_print_binary(ip->first_host_ip, ip->mask_size);
	printf(NL);
	ft_print_section("to:");
	ft_print_binary(ip->last_host_ip, ip->mask_size);
	printf(NL NL);
}

void			ft_print_decimal(t_32bits addr)
{
	printf("%d", addr.octets[0]);
	for (int i = 1; i < 4; ++i)
		printf(".%d", addr.octets[i]);
}

void			ft_print_binary(t_32bits addr, int mask_size)
{
	int i;
	int j;

	printf(COLOR);
	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 8; ++j)
		{
			if (i * 8 + j + 1 > mask_size)
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
