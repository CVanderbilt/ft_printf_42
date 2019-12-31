/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:32:54 by eherrero          #+#    #+#             */
/*   Updated: 2019/11/11 13:11:55 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*p;

	i = -1;
	p = (char*)s;
	while (p[++i])
		if (p[i] == c)
			return (p + i);
	if (p[i] == c)
		return (p + i);
	else
		return (0);
}