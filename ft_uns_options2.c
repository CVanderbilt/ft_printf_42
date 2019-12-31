/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uns_options2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 14:12:56 by eherrero          #+#    #+#             */
/*   Updated: 2019/12/31 14:22:15 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_check_prefix(t_data *data, char *s, char *pref)
{
	if (!pref)
		return (s);
	if (data->actual_type == 'o' && s[0] == '0')
		return (s);
	return (ft_arraynjoinfree_r(pref, s, ft_strlen(pref), ft_strlen(s) + 1));
}

char	*ft_check_prefix_mod(char *str)
{
	int i;
	int zero_pos;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] != '0' || ft_in_set("xX", str[i + 1]))
		return (str);
	zero_pos = i;
	while (str[i] == '0')
		i++;
	if (ft_in_set("xX", str[i]))
	{
		str[zero_pos + 1] = str[i];
		str[i] = '0';
	}
	return (str);
}

char	*ft_prefix_select(t_data *data, char type, unsigned long long int n)
{
	if (type == 'p')
		return (ft_strdup("0x"));
	if (data->hash_flag && ft_in_set("xX", type) && n != 0)
		return (type == 'x' ? ft_strdup("0x") : ft_strdup("0X"));
	if (data->hash_flag && type == 'o')
		return (ft_strdup("0"));
	return (0);
}
