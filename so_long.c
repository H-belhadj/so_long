// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   so_long.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/05/14 16:46:14 by hbelhadj          #+#    #+#             */
// /*   Updated: 2023/05/15 17:39:55 by hbelhadj         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

 #include "so_long.h"

int main(int argc, char **argv)
{
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
    int exit;
    int collec;
    int start;
    int row_length;

    
    if(argc != 2)
    {
        printf("ERROR : Invalid number of arguments\n");
        return (1);
    }

    extension = ".ber";
    map_file = argv[1];
    if(ft_strlen(map_file) < ft_strlen(extension) || strcmp(map_file + ft_strlen(map_file) - ft_strlen(extension), extension) != 0)
    {
        printf("ERROR : map filename must have .ber extenstion\n");
        return (1);
    }

    fd = open(argv[1], O_RDONLY);
    cnt = 1;
    total = NULL;
    while(1)
    {
        str = get_next_line(fd);
        if(!str)
            break;
        total = ft_strjoin(total,str);
        cnt++;
    }
    close(fd);
    
    stored = ft_split(total,'\n');

    i = 0;
    exit = 0;
    collec = 0;
    start = 0;
    row_length = ft_strlen(stored[0]);
    while(stored[i])
    {
        j = 0;
        while(stored[i][j])
        {
            allowed_char = "01CEP";
            if(!strchr(allowed_char, stored[i][j]))
            {
                printf("WARNING : The map can be composed of only these 5 characters: 0, 1, C, E, P\n");
                return (1);
            }
            if(stored[i][j] == 'E')
                exit++;
            else if(stored[i][j] == 'C')
                collec++;
            else if (stored[i][j] == 'P')
                start++; 
            j++;
        }
        if(ft_strlen(stored[i]) != row_length)
        {
            printf("ERROR : The map is not rectangular.\n");
            return (1);

        }
        i++;
    }
    i = 0;
    while (stored[0][i] != '\0')
    {
        if(stored[0][i] != '1' || stored[cnt - 2][i] != '1')
        {
            printf("ERROR : The map must be surrounded by walls.\n");
            return (1);
        }
        i++;
    }
    i = 0;
    while(stored[i] != NULL)
    {
        if(stored[i][0] != '1' || stored[i][row_length - 1] != '1')
        {
            printf("ERROR : The map must be surrounded by walls.\n");
            return (1);
        }
        i++;
    }
    
    if (exit != 1 || collec < 1 || start != 1)
    {
        if(exit > 1 || start > 1)
        {
            printf("ERROR : The map must not contain duplicates of characters (exit/start).\n");
            return (1);
        }
        printf("ERROR : The map must contain 1 exit, at least 1 collectible, and 1 starting position to be valid");
        return (1);
    }
    printf("YOUR MAP IS GOOD\n");
    free(stored);
}