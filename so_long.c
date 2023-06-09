#include "so_long.h"

typedef struct  s_list{
    int     position[2];  // Player position [X, Y]
    char    **map;  // Map data
    char    **fake_map; //Fake maps ............0
    int     moves; // how many times the player moved
    void    *wll;
    void    *backgound;
    void    *door; 
    void    *player;
    void    *coins;
    void    *win;
    void    *mlx;
    int     coin_count; // Number of coins remaining
    int     plyer_x;
    int     plyer_y;
} t_list;

void search_player(t_list *so_long)
{
    int i;
    int j;

    i = -1;
    while(so_long->map[++i])
    {
        j = -1;
        while(so_long->map[i][++j])
        {
            if (so_long->map[i][j] == 'P')
            {
                so_long->plyer_x = j;
                so_long->plyer_y = i;
                return ;
            }
        }
    }
}

int check_existance(char **fake_map)
{
    int i;
    int j;

    i = -1;
    while(fake_map[++i])
    {
        j = -1;
        while(fake_map[i][++j])
        {
            if(fake_map[i][j] == 'E')
                return (1);
            else if(fake_map[i][j] == 'C')
                return (1);
            else if(fake_map[i][j] == 'P')
                return (1);
        }
    }
    return (0);
}

void back_track(t_list *so_long, int x, int y)
{
    if(so_long->fake_map[x][y + 1] != '1' && so_long->fake_map[x][y + 1] != 'x')
    {
        so_long->fake_map[x][y + 1] = 'x';
        back_track(so_long, x, y + 1);
    }
    if (so_long->fake_map[x - 1][y] != '1' && so_long->fake_map[x - 1][y] != 'x')
    {
        so_long->fake_map[x - 1][y] = 'x';
        back_track(so_long, x - 1, y);
    }
    if (so_long->fake_map[x][y - 1] != '1' && so_long->fake_map[x][y - 1] != 'x')
    {
        so_long->fake_map[x][y - 1] = 'x';
        back_track(so_long, x, y - 1);
    }
    if (so_long->fake_map[x + 1][y] != '1' && so_long->fake_map[x + 1][y] != 'x')
    {
        so_long->fake_map[x + 1][y] = 'x';
        back_track(so_long, x + 1, y);
    }
}

int update(t_list *so_long)
{
    int i;
    int j;

    i = -1;
    while (so_long->map[++i]) {
        j = -1;
        while (so_long->map[i][++j]) {
            if (so_long->map[i][j] == '0')
                mlx_put_image_to_window(so_long->mlx, so_long->win, so_long->backgound, j * 50, i * 50);
            if (so_long->map[i][j] == '1')
                mlx_put_image_to_window(so_long->mlx, so_long->win, so_long->wll, j * 50, i * 50);
            if (so_long->map[i][j] == 'C')
                mlx_put_image_to_window(so_long->mlx, so_long->win, so_long->coins, j * 50, i * 50);
            if (so_long->map[i][j] == 'E')
            {
                mlx_put_image_to_window(so_long->mlx, so_long->win, so_long->backgound, j * 50, i * 50);
                mlx_put_image_to_window(so_long->mlx, so_long->win, so_long->door, j * 50, i * 50);

            }
            if (so_long->map[i][j] == 'P')
                mlx_put_image_to_window(so_long->mlx, so_long->win, so_long->backgound, j * 50, i * 50);
        }
    }
    mlx_put_image_to_window(so_long->mlx, so_long->win, so_long->player, so_long->position[X] , so_long->position[Y] );
    if ( so_long->coin_count == 0 && so_long->map[so_long->position[Y] / 50][so_long->position[X] / 50] == 'E') 
        exit(0);
    return (0);
}

int hook(int keycode, t_list *so_long)
{
    if (keycode == 53)
        exit(0);
    if (keycode == 124) // Right arrow key
    {
        if (so_long->map[so_long->position[Y] / 50][so_long->position[X] / 50 + 1] != '1') 
        {
            so_long->position[X] += 50;
            so_long->moves++;
        }
    }
    if (keycode == 123) // Left arrow key
    {
        if (so_long->map[so_long->position[Y] / 50][so_long->position[X] / 50 - 1] != '1')
         {
            so_long->position[X] -= 50;
            so_long->moves++;
        }
    }
    if (keycode == 125) // Down arrow key
    {
        if (so_long->map[so_long->position[Y] / 50 + 1][so_long->position[X] / 50] != '1') 
        {
            so_long->position[Y] += 50;
            so_long->moves++;
        }
    }
    if (keycode == 126) // Up arrow key
    {
        if (so_long->map[so_long->position[Y] / 50 - 1][so_long->position[X] / 50] != '1') 
        {
            so_long->position[Y] -= 50;
            so_long->moves++;
        }
    }

    // Check if the player collected a coin
    if (so_long->map[so_long->position[Y] / 50][so_long->position[X] / 50] == 'C')
    {
        so_long->map[so_long->position[Y] / 50][so_long->position[X] / 50] = '0';
        so_long->coin_count--;
    }

    // Check if the game is over (all coins collected and player at the exit)
    if ( so_long->coin_count ==0 && so_long->map[so_long->position[Y] / 50][so_long->position[X] / 50] == 'E') 
    {
        printf("Congratulations! You collected all the coins and reached the exit!\n");
        exit(0);
    }
    printf("movement: %d\n", so_long->moves);

    return (1);
}



int main(int argc, char **argv)
{
    t_list *so_long = malloc(sizeof(t_list));
    char **stored;
    char *extension;
    char *map_file;
    char *str;
    char *total;
    char *allowed_char;
    int fd;
    int cnt;
    int i; 
    int j;
    int exit_count;
    int collec_count;
    int start_count;
    int row_length;
    if (argc != 2) {
        printf("ERROR: Invalid number of arguments\n");
        return (1);
    }

    extension = ".ber";
    map_file = argv[1];
    if (ft_strlen(map_file) < ft_strlen(extension) || strcmp(map_file + ft_strlen(map_file) - ft_strlen(extension), extension) != 0) {
        printf("ERROR: Map filename must have .ber extension\n");
        return (1);
    }

    fd = open(argv[1], O_RDONLY);
    cnt = 1;
    total = NULL;
    while (1) {
        str = get_next_line(fd);
        if (!str)
            break;
        total = ft_strjoin(total, str);
        cnt++;
    }
    close(fd);
    so_long->map = ft_split(total, '\n');
    so_long->fake_map = ft_split(total, '\n');
    search_player(so_long);

    back_track(so_long, so_long->plyer_x, so_long->plyer_y);
   
    if (check_existance(so_long->fake_map) == 1)
    {
        printf ("Error\n invalid path");
        return (1);
    }
    so_long->moves = 0;

    i = 0;
    exit_count = 0;
    start_count = 0;
    int player_pos[2];

    row_length = ft_strlen(so_long->map[0]);
    while (so_long->map[i]) {
        j = 0;
        while (so_long->map[i][j]) {
            allowed_char = "01CEP";
            if (!strchr(allowed_char, so_long->map[i][j])) {
                printf("WARNING: The map can only contain these 5 characters: 0, 1, C, E, P\n");
                return (1);
            }
            if (so_long->map[i][j] == 'E')
                exit_count++;
            else if (so_long->map[i][j] == 'C')
                collec_count++;
            else if (so_long->map[i][j] == 'P') {
                player_pos[X] = j * 50;
                player_pos[Y] = i * 50;
                start_count++;
            }
            j++;
        }
        if (ft_strlen(so_long->map[i]) != row_length) {
            printf("ERROR: The map is not rectangular.\n");
            return (1);
        }
        i++;
    }
    so_long->coin_count = collec_count;

    i = 0;
    while (so_long->map[0][i] != '\0') {
        if (so_long->map[0][i] != '1' || so_long->map[cnt - 2][i] != '1') {
            printf("ERROR: The map must be surrounded by walls.\n");
            return (1);
        }
        i++;
    }

    i = 0;
    while (so_long->map[i] != NULL) {
        if (so_long->map[i][0] != '1' || so_long->map[i][row_length - 1] != '1') {
            printf("ERROR: The map must be surrounded by walls.\n");
            return (1);
        }
        i++;
    }
    
    if (exit_count != 1 || collec_count < 1 || start_count != 1) {
        if (exit_count > 1 || start_count > 1) {
            printf("ERROR: The map must not contain duplicates of characters (exit/start).\n");
            return (1);
        }
        printf("ERROR: The map must contain 1 exit, at least 1 collectible, and 1 starting position to be valid.\n");
        return (1);
    }

    printf("YOUR MAP IS GOOD\n");

    int high = 50;
    int width = 50;
    so_long->mlx = mlx_init();
    so_long->win = mlx_new_window(so_long->mlx, ft_strlen(so_long->map[0]) * 50, (cnt-1) * 50, "tangawi w rassi 3ali so_long");
    so_long->wll = mlx_xpm_file_to_image(so_long->mlx, "textures/wall.xpm", &high, &width);
    so_long->door = mlx_xpm_file_to_image(so_long->mlx, "textures/door.xpm", &high, &width);
    so_long->player = mlx_xpm_file_to_image(so_long->mlx, "textures/player.xpm", &high, &width);
    so_long->coins = mlx_xpm_file_to_image(so_long->mlx, "textures/coin.xpm", &high, &width);
    so_long->backgound = mlx_xpm_file_to_image(so_long->mlx, "textures/backgound.xpm", &high, &width);
    

    so_long->position[X] = player_pos[X];
    so_long->position[Y] = player_pos[Y];

    printf("ok\n");
    mlx_hook(so_long->win, ON_KEYDOWN, 1 << 0, hook, so_long);
    mlx_loop_hook(so_long->mlx,update,so_long);
    mlx_loop(so_long->mlx);
    // free(so_long->map);
    // free(so_long);
}
