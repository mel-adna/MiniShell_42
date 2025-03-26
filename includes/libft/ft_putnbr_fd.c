/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:29:33 by mel-adna          #+#    #+#             */
/*   Updated: 2024/11/18 15:21:17 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lennum(int i)
{
	int		temp;
	int		len1;

	temp = i;
	len1 = 0;
	if (i <= 0)
		len1 = 1;
	while (temp)
	{
		len1++;
		temp /= 10;
	}
	return (len1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int			len;
	int			is_n;
	long int	num;
	char		str[12];

	num = n;
	len = ft_lennum(n);
	str[len] = '\0';
	is_n = (num < 0);
	if (is_n)
		num = -num;
	while (len-- > 0)
	{
		str[len] = '0' + (num % 10);
		num /= 10;
	}
	if (is_n)
		str[0] = '-';
	ft_putstr_fd(str, fd);
}
