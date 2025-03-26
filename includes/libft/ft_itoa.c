/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 09:18:01 by mel-adna          #+#    #+#             */
/*   Updated: 2024/11/18 17:38:18 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int i)
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

char	*ft_itoa(int n)
{
	int			len;
	int			is_n;
	int long	num;
	char		*str;

	num = n;
	len = ft_numlen(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
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
	return (str);
}
