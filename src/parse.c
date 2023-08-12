/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:33:05 by ayaman            #+#    #+#             */
/*   Updated: 2023/02/02 13:33:07 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	Bu fonksiyon bizim girilen map adı argümanının
	kontrol edildiği fonksiyondur. Eğer girilen argümanda
	bir sıkıntı var ise error yazdırma fonksiyonlarına 
	gönderme işlemi yapılır.
*/

void	check_arg(int argc, char **argv)
{
	int		i;
	int		fd;

	if (argc != 2)
		exit_err("Input Argument Error\n");
	i = ft_strlen(argv[1]) - 4;
	if (ft_strncmp(&argv[1][i], ".cub", 4))
		exit_err("File Extension Error\n");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		system_err(".cub Path Error");
	if (close(fd) < 0)
		system_err("Close Failed Error");
}

/*
	Bu fonksiyon oyunun durumunu ve dosyadan okunan bir satırı
	tutar. Ayrıyetten oyunun dokularının, zemin ve tavan renklerinin
	belirlenip belirlenmediğini kontrol eder. Eğer bu değişkenlerin
	değeri 4'ten büyük veya 2'den büyük ise fazla bilgi verildiği
	anlamına gelir ve error mesajını yazdırıp programı sonlandırır.
*/

void	parse_line(t_game *game, char *line)
{
	if (game->dir_flag > 4 || game->color_flag > 2)
		exit_err(".cub: Too Much gamermation Error\n");
	else if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) || \
		!ft_strncmp(line, "EA ", 3) || !ft_strncmp(line, "WE ", 3))
		get_textures(line, game);
	else if (!ft_strncmp(line, "F ", 2))
		get_background_color(line, game, FLOOR);
	else if (!ft_strncmp(line, "C ", 2))
		get_background_color(line, game, CEILING);
	else if (ft_strlen(line) <= 0)
		return ;
	else if (game->color_flag == 2 && game->dir_flag == 4)
		parse_map(line, game);
	else
		exit_err(".cub: Invalid Identifier Error\n");
}

/*
	Bu fonksiyon gnl ile harita dosyasını okur. Eğer okuma 
	işlemi yapılamamışsa hata mesajı döndürür. Lakin okuma  işlemi
	başarı bir şekilde gerçekleştiyse parse_line fonksiyonu ile
	okunan satırı işler. Parse_line fonskiyonu satırdaki oyun ayarlarını
	veya harita bilgisini alır ve game yapısına kaydeder. Dosyanın 
	sonuna gelene kadar bu fonksiyon devam eder. Dosyanın son satırını
	işlemek için parse_last fonksiyonu son satırdaki harita bilgisini alır ve 
	game yapısına kayıt eder. 
*/

void	parse_cub(int fd, t_game *game)
{
	char	*line;

	while (get_next_line(fd, &line) > 0)
	{
		if (!line)
			exit_err("GNL Error\n");
		parse_line(game, line);
		free(line);
	}
	parse_last(game, line);
	free(line);
	if (game->dir_flag != 4 || game->color_flag != 2 || game->pos_flag != 1)
		exit_err(".cub: Too Few gamermation\n");
}

/*
	Bu fonksiyonda ilk başta argüman kontrolü yapıldıktan sonra
	girilen harita dosyasını açıp, açılıp açılmadığını kontrol 
	ediyoruz. Eğer açıldıysa parse_cub fonksiyonuna yönlendirme işlemi yapılır. 
*/

void	parse(int argc, char **argv, t_game *game)
{
	int		fd;

	check_arg(argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_err("Map Path Error\n");
	parse_cub(fd, game);
	close(fd);
}
