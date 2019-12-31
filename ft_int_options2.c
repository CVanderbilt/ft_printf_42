/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_options2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 14:19:06 by eherrero          #+#    #+#             */
/*   Updated: 2019/12/31 14:20:10 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_width_int(t_data *data, char *str)
{
	char	*ret;
	char	blank;
	int		str_start;
	int		blank_start;
	int		size;

	if (!(ret = malloc(data->width + 1)))
		return (0);
	ret[data->width] = 0;
	size = ft_strlen(str);
	blank = ' ';
	str_start = 0;
	blank_start = size;
	if (!data->minus_flag)
	{
		blank = data->zero_flag ? '0' : ' ';
		str_start = data->width - size;
		blank_start = 0;
	}
	ft_memset(ret + blank_start, blank, data->width - size);
	ft_memmove(ret + str_start, str, size);
	free(str);
	return (ret);
}

char	*ft_precision_int(t_data *data, char *str)
{
	char	*ret;
	int		len;

	len = ft_strlen(str);
	if (data->precision < len)
	{
		if (len == 1 && str[0] == '0' && data->precision >= 0)
		{
			free(str);
			return (ft_strdup(""));
		}
		else
			return (str);
	}
	ret = ft_calloc(data->precision + 1, 1);
	if (!ret)
		return (str);
	ret[data->precision] = 0;
	ft_memmove(ret + data->precision - len, str, len);
	free(str);
	return (ret);
}

char	*ft_check_sign(char *str)
{
	int		i;
	int		frst_dgt;
	int		sign_pos;
	char	tmp;

	i = 0;
	while (str[i] == ' ')
		i++;
	frst_dgt = i;
	while (str[i] == '0')
		i++;
	if (!str[i] || ft_isdigit(str[i]))
		return (str);
	if (str[i] == ' ' && (str[i + 1] == ' ' || !str[i + 1]))
		return (str);
	sign_pos = i;
	tmp = str[sign_pos];
	str[sign_pos] = str[frst_dgt];
	str[frst_dgt] = tmp;
	return (str);
}
