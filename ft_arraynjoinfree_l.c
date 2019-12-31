/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraynjoinfree_l.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 13:54:54 by eherrero          #+#    #+#             */
/*   Updated: 2019/12/31 13:56:54 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_arraynjoinfree_l(void *s1, void *s2, int n1, int n2)
{
	char	*ret;

	ret = ft_arraynjoin(s1, s2, n1, n2);
	if (!ret)
		return (0);
	free(s1);
	return (ret);
}
