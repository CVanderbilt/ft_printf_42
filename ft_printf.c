/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 14:05:31 by eherrero          #+#    #+#             */
/*   Updated: 2019/12/31 14:33:05 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *str, ...)
{
	t_data	data;

	ft_data_init(&data, str);
	va_start(g_args, str);
	while (str[data.pos])
	{
		if (str[data.pos] == '%')
		{
			data.pos++;
			ft_state_flags(&data);
		}
		else
		{
			ft_save_chr(&data, data.str[data.pos]);
			data.pos++;
		}
		ft_reinit_data(&data);
	}
	ft_printnchr_fd(data.out, data.size, 1);
	ft_free_data(&data);
	return (data.size);
}
