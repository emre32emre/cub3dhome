/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:32:49 by ayaman            #+#    #+#             */
/*   Updated: 2023/06/14 17:16:04 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	Bu fonksiyon ilk başta 'mlx_xpm_file_to_image' fonksiyonu ile imagemizin yüksekliğini ve genişliğini bulur.
	Daha sonra 'mlx_get_data_addr' fonksiyonunu kullanarak dokunun renk verilerini alır ve img.data değişkenine atar. 
	Bu fonksiyon, aynı zamanda dokunun bit derinliğini img.bpp değişkenine atar.
	iki tane döngü kullanarak dokunun renk verilerini texture dizisine kopyalar. 
	Bu döngüler, dokunun her pikselini gezerek texture dizisinin uygun elemanına renk değerini atar. 
	Renk değerleri 256 tabanına göre dönüştürülmüştür.
*/

void	load_image(t_game *game, int *texture, char *path)
{
	t_img	img;
	int		x;
	int		y;

	img.img = \
	mlx_xpm_file_to_image(game->mlx, path, &img.img_width, &img.img_height);
	img.data = \
	(int *)mlx_get_data_addr(img.img, &img.bpp, &img.bpp, &img.bpp);
	y = -1;
	while (++y < img.img_height)
	{
		x = -1;
		while (++x < img.img_width)
			texture[img.img_width * y + x] = img.data[img.img_width * y + x];
	}
	mlx_destroy_image(game->mlx, img.img);
}

/*
	Bu fonksiyon harita dosyanın son 4 harfini kontrol eder
	(example-> map.pub). Bunu da dosya adının ilk harfinden
	ilerleyip son dört karaktere gelip burada bi karşılaştırma
	işlemi yapıyor. Eğer bir sıkıntı var ise error mesajı yazırıp
	programdan çıkılıyor.
*/

int	check_extension(char *filename, char *extension)
{
	if (!filename)
		return (EXIT_FAILURE);
	if (ft_strncmp(filename + ft_strlen(filename) - 4, extension, 4))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
	Bu fonksiyonda ise get_textures'den aldığımız değişkenlerin
	kontolünü yapıyoruz. Eğer girilen argüman sayısı 2'ye eşit değil
	ise ve ikinci argüman ".xpm" ile bitmiyorsa split değişkenini freeleyip
	hata çıktısı döndürür. Lakin istenilen şekilde argüman girildiyse dosya 
	açılıp dosyadan dokuyu okuyup game->texture değişkenine doldurur.
	daha sonra dir_flag(kaç tane doku tutulduğunu belirten değişken)
	değişkenini arttırır.
*/

int	get_texture(char *line, t_game *game, int dir)
{
	int		fd;
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		system_err("Malloc Error");
	if (ft_splitlen(split) != 2 || check_extension(split[1], ".xpm"))
	{
		free_double_char(split);
		return (RETURN_FAILURE);
	}
	fd = open(split[1], O_RDONLY);
	if (fd < 0)
		return (RETURN_FAILURE);
	load_image(game, game->texture[dir], split[1]);
	free_double_char(split);
	game->dir_flag++;
	return (RETURN_SUCCESS);
}

/*
	Bu fonksiyon mapte kuzey güney doğu batı kontorlü yapar.
	eğer bunlardan bir tanesi eksikse map hata verir. Çünkü biz mapte
	duvarları tek bir renk yapmıyoruz. Haritamız da iki boyutlu olduğu için 
	kamera açımızın baktığı yere göre duvara renk vermemiz gerekiyor.
*/

int	get_textures(char *line, t_game *game)
{

	if (!ft_strncmp(line, "NO ", 3))
	{
		if (get_texture(line, game, NO))
			exit_err("Map: Invalid Texture Value\n");
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		if (get_texture(line, game, EA))
			exit_err("Map: Invalid Texture Value\n");
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		if (get_texture(line, game, SO))
			exit_err("Map: Invalid Texture Value\n");
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		if (get_texture(line, game, WE))
			exit_err("Map: Invalid Texture Value\n");
	}
	return (RETURN_SUCCESS);
}
