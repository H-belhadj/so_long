/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 20:10:04 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/09/14 15:30:51 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>
# include "get_next_line.h"
# include <mlx.h>

typedef struct s_list{
	int		position[2];
	char	**map;
	char	**fake_map;
	int		moves;
	void	*wll;
	void	*backgound;
	void	*door; 
	void	*player;
	void	*coins;
	void	*win;
	void	*mlx;
	int		coin_count;
	int		plyer_x;
	int		plyer_y;
}t_list;

typedef struct s_value{
	char		*str;
	char		*total;
	char		*allowed_char;
	int			cnt;
	int			i; 
	int			j;
	int			exit_count;
	int			collec_count;
	int			start_count;
	int			row_length;
	int			high;
	int			width;
	int			player_pos[2];

}t_value;

char			*ft_strdup(char *s);
char			*ft_substr(char *s, unsigned int start, int len);
int				ft_count_world(char *s, char c);
char			**ft_split(char *s, char c);
void			process_tile(t_list *so_long, int i, int j);
void			short_update(t_list *so_long, int *i, int *j);
int				update(t_list *so_long);
void			move_right(t_list *so_long);
void			move_left(t_list *so_long);
void			move_down(t_list *so_long);
void			move_up(t_list *so_long);
void			collect_coin(t_list *so_long);
int				hook(int keycode, t_list *so_long);
int				walls_error(t_list *so_long, t_value *value);
int				walls_error_2(t_list *so_long, t_value *value);
int				char_error_1(t_list *so_long, t_value *value);
int				char_error(t_list *so_long, t_value *value);
int				split_main(t_list *so_long, t_value *value);
void			short_main(t_list *so_long, t_value *value);
int				start_end_error(t_value *value);
void			search_player(t_list *so_long);
int				check_existance(char **fake_map);
void			back_track(t_list *so_long, int x, int y);
void			file_ber(char **argv);
int				ft_strcmp(char *s1, char *s2);
void			free_2d(char **m);
void			empty_file(char *file);
int				ft_small(t_list *so_long, t_value *value, int i);
char			*ft_putstr(char *str);
void			ft_putnbr(int num);
int				ft_close(void);

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum {
	X,
	Y
};

#endif
