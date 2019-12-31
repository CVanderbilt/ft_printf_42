/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraynjoinfree_r.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 13:56:09 by eherrero          #+#    #+#             */
/*   Updated: 2019/12/31 13:56:32 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_arraynjoinfree_r(void *s1, void *s2, int n1, int n2)
{
	char	*ret;

	ret = ft_arraynjoin(s1, s2, n1, n2);
	if (!ret)
		return (0);
	free(s2);
	return (ret);
}
