/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:33:34 by ayaman            #+#    #+#             */
/*   Updated: 2023/02/02 13:33:34 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	exit_err(char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
	exit(EXIT_FAILURE);
}

/*
	Gönderilen sistem hata mesajını çıktı yapıp programı sonlandırır.
*/

void	system_err(char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}

/*
	Bu fonksiyonda freeleme işleminden sonra hata çıktısı ekrana yazdırılıp program sonlandırılır.
*/

void	free_exit_err(char **str, char *err_msg)
{
	int		i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	ft_putstr_fd(err_msg, 2);
	exit(EXIT_FAILURE);
}

int	free_return_err(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (RETURN_FAILURE);
}
