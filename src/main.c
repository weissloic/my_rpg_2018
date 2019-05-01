/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** main
*/

#include "../include/rpg.h"
#include "../include/my.h"

int check_env(char **env)
{
    for (int i = 0; env[i + 1] != NULL; i++) {
        if (my_strncmp(env[i], "DISPLAY", 8) == 0)
            return (0);
    }
    return (84);
}

int display_help(void)
{
    int fd;
    int size;
    char buff[460];

    fd = open("ressources/text/help", O_RDONLY);
    if (fd < 0)
        return (84);
    size = read(fd, buff, sizeof(buff));
    if (size <= 0)
        return (84);
    my_printf(buff);
    close(fd);
    return (0);
}

void reset_player(window_t *win)
{
    win->no_saves = 1;
    win->player = malloc(sizeof(player_t) * 1);
    win->player->sprite = malloc(sizeof(sprite_t) * 1);
    win->player->name = NULL;
    win->player->sprite->sprite = NULL;
    win->player->sprite->texture = NULL;
    win->player->strength = 0;
    win->player->health = 0;
    win->player->actual_health = 0;
    win->player->xp = 0;
    win->player->last_pos = get_pos_float(-100, -100);
    win->player->direction = 1;
    win->player->move_rect = 0;
    win->player->last_page = CASTLE;
    win->inv = NULL;
    win->quests = NULL;
    save_config_player(win);
}

void check_error_config(window_t *win)
{
    if (win->player == NULL || win->player->last_page == END)
        reset_player(win);
    if (win->player->last_pos.x < 0)
        win->no_saves = 1;
    if (win->inv == NULL) {
        win->no_saves = 1;        
        win->inv = malloc(sizeof(inventory_t) * 1);
        win->inv->sprite = malloc(sizeof(sprite_t) * 1);
        win->inv->items = malloc(sizeof(items_t) * 15);
        for (int i = 0; i < 15; i++)
            win->inv->items[i].name = NULL;
        save_inventory(win);
    }
    if (win->quests == NULL) {
        win->no_saves = 1;
        win->quests = malloc(sizeof(quest_t) * 1);
        win->quests->sprite = malloc(sizeof(sprite_t) * 6);
        win->quests->text = malloc(sizeof(text_t) * 5);
        win->quests->quete_done = 0;
        save_quests(win);
    }
}

int main(int ac, char **av, char **env)
{
    window_t *win = malloc(sizeof(window_t) * 1);

    if (win == NULL || env == NULL || env[0] == NULL || check_env(env) == 84)
        return (84);
    if (ac == 2 && my_strcmp(av[1], "-h") == 0)
        return (display_help());
    win = create_window(win);
    init_music(win->music);
    win->player = parser_player(win->player, "ressources/text/config_player");
    win->inv = parser_inv(win->inv, "ressources/text/inventory");
    win->quests = parser_quests(win->quests, "ressources/text/quests");
    check_error_config(win);
    if (display(win) == 84) {

        destroy_all(win);
        return (84);
    }
    destroy_all(win);
    return (0);
}