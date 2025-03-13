#include "./cub3d.h"

void    print_player(const t_player *player)
{
    printf("Player Position: (%d, %d)\n", player->pos_x, player->pos_y);
    printf("Direction: (%d)º\n", player->dir);
}