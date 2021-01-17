/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:24:39 by aezzara           #+#    #+#             */
/*   Updated: 2021/01/03 19:39:39 by aezzara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 
** This Function search for a char in a string. If char is found in a string
** then return 1, else 0
*/
int is_found(char *str, char c)
{
	while (*str)
		if (*str++ == c)
			return (1);
	return (0);
}

/* 
** This function cheks that a char in a string founds exactly n-times.
** If char is founded in a string more or less than n-times, then return 0,
** otherwise return 1.
*/
int is_char_n_times(char *str, char c, int n)
{
	int	counter = 0;
	while (*str)
		if (*str++ == c)
			counter++;
	return ((n == counter) ? 1 : 0);
}

void	print_octets(int *octets)
{
	int i = 0;
	
	printf("\t");
	while (i < 3)
		printf("%d.", octets[i++]);
	printf("%d", octets[i]);
}

void	print_bin_octets(int *octets)
{
	int n = 0;
	int i;
	int p;
	int	cp_octets[4] = {0};

	printf("\t\t");
	while (n < 4)
	{
		i = 0;
		p = 128;
		cp_octets[n] = octets[n];
		while (p)
		{
			if (cp_octets[n] >= p)
			{
				printf("1");
				cp_octets[n] = cp_octets[n] - p;
			}
			else
				printf("0");
			p = p / 2;
		}
		if (n < 3)
			printf(".");
		n++;
	}
}

int		ft_two_power(int n)
{
	int res = 1;

	while (n--)
		res = res * 2;
	return (res);		
}

void	calc_mask(int *mask, int *reverse_mask)
{
	int i = 0;
	int n = -1;

	while (i < mask[4])
	{
		if ((i % 8) == 0)
			n++;
		mask[n] += ft_two_power(7 - (i % 8));
		reverse_mask[n] += 0;
		i++;
	}
	while (i < 32)
	{
		if ((i % 8) == 0)
			n++;
		mask[n] += 0;
		reverse_mask[n] += ft_two_power(7 - (i % 8));
		i++;
	}
}

int main(int ac, char **av)
{
	int octets[5] = {0};
	int mask[5] = {0};
	int reverse_mask[5] = {0};
	int res_octets[5] = {0};
	int wide_address[5] = {0};
	int count_address = 1;
	char *tmp;

/*
** Part that checks for correct argv
*/
	if (ac != 2)
	{
		printf("Number of argc not 2!\n");
		return (0);
	}
	else if (!is_found(av[1], '/'))
	{
		printf("no symbol \'/\'\n");
		return (0);
	}
	else if (!is_char_n_times(av[1], '.', 3))
	{
		printf("symbol \'.\' less than 3 times\n");
		return (0);
	}

	tmp = strrchr(av[1], '/');
	mask[4] = atoi(tmp + 1);
	*tmp = '\0';
	
	int i = 3;
	while (i > 0)
	{
		tmp = strrchr(av[1], '.');
		octets[i--] = atoi(tmp + 1);
		*tmp = '\0';
	}
	octets[0] = atoi(av[1]);
	printf("IP adress\n");
	print_octets(octets);
	print_bin_octets(octets);

	printf("\nMask\n");
	calc_mask(mask, reverse_mask);
	print_octets(mask);
	print_bin_octets(mask);
	
	printf("\nReverse Mask\n");
	print_octets(reverse_mask);
	print_bin_octets(reverse_mask);

	i = 0;
	while (i < 4)
	{
		res_octets[i] = octets[i] & mask[i];
		i++;
	}
	printf("\nNetwork address of a host\n");
	print_octets(res_octets);
	print_bin_octets(res_octets);

	i = 0;
	while (i < 4)
	{
		wide_address[i] = octets[i] | reverse_mask[i];
		i++;
	}
	printf("\nWide address\n");
	print_octets(wide_address);
	print_bin_octets(wide_address);

	i = 0;
	while (i < 4)
	{
		count_address = count_address * (wide_address[i] - res_octets[i] + 1);
		i++;
	}
	printf("\nCount of available addresses\n");
	printf("\t%d", count_address);

	printf("\nMaximum numbers of IP address\n");
	printf("\t%d", count_address - 2);
	
	printf("\nFirst host IP address\n");
	res_octets[3] += 1;
	print_octets(res_octets);
	print_bin_octets(wide_address);

	printf("\nLast host IP address\n");
	wide_address[3] -= 1;
	print_octets(wide_address);
	print_bin_octets(wide_address);
	return (0);

}
