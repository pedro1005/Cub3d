#include "./cub3d.h"

//move player and return 1. if doesn't move, return 0.
int move_player(t_player *player, int **map)
{
    float rad = player->dir * (M_PI / 180.0); // Convert direction to radians

    // Calculate new potential position using float for precision
    float new_pos_x = player->pos_x - (STEP_SIZE * cos(rad));
    float new_pos_y = player->pos_y - (STEP_SIZE * sin(rad));

    // Convert to integer for map grid checking
    int map_pos_x = (int)new_pos_x;
    int map_pos_y = (int)new_pos_y;

    if (map_pos_x >= 0 && map_pos_y >= 0 && 
        map_pos_x < get_xlen(map) && map_pos_y < get_ylen(map))
    {
        // Update player's position with float precision
        player->pos_x = new_pos_x;
        player->pos_y = new_pos_y;

        if (map[map_pos_y][map_pos_x] == 1)
        {
            map[map_pos_y][map_pos_x] = 5;
            return (0);
        }

        // Debugging visualization (remove in production)
        map[map_pos_y][map_pos_x] = 5;

        return 1;
    }
    return 0;
}



/*void rotate_player(t_player *player, float angle)
{
    // Convert angle from degrees to radians
    float radians = angle * (M_PI / 180.0);

    // Save the current direction
    float temp_dir_x = player->dir_x;

    // Apply rotation formula
    player->dir_x = player->dir_x * cos(radians) - player->dir_y * sin(radians);
    player->dir_y = temp_dir_x * sin(radians) + player->dir_y * cos(radians);
}*/



void    print_player(const t_player *player)
{
    printf("Player Position: (%d, %d)\n", player->pos_x, player->pos_y);
    printf("Direction: (%.2f)º\n", player->dir);
}